import json
import os
import urllib.request
import subprocess
from os import path

# 1.18.2 server direct download link
SERVER_URL = 'https://launcher.mojang.com/v1/objects/c8f83c5655308435b3dcf03c06d9fe8740a77469/server.jar'

# setup constants
BOOTSTRAP_DIR = path.abspath('./bootstrap')
SERVER_PATH = path.join(BOOTSTRAP_DIR, 'server.jar')
REPORTS_DIR = path.join(BOOTSTRAP_DIR, 'reports')

GEN_HEADER_PATH = path.join('mc-proto', 'minecraft', 'generated.h')
GEN_SOURCE_PATH = path.join('mc-proto', 'minecraft', 'generated.cpp')

FILE_HEADER_COMMENT = \
"""
// generated by bootstrap.py
// do not modify
"""

# setting up all data for bootstrap
if not path.exists(BOOTSTRAP_DIR):
    os.mkdir(BOOTSTRAP_DIR)

if not path.exists(SERVER_PATH):
    print('Downloading server jar...')
    urllib.request.urlretrieve(SERVER_URL, SERVER_PATH)

# generating raw data
if not path.exists(REPORTS_DIR):
    os.mkdir(REPORTS_DIR)

if len(os.listdir(REPORTS_DIR)) == 0:
    print('Generating raw data...')
    subprocess.run(
        f'java "-DbundlerMainClass=net.minecraft.data.Main" -jar {SERVER_PATH} -reports -all --output="{BOOTSTRAP_DIR}"', 
        cwd=BOOTSTRAP_DIR
    )

# generating type code from reports
if path.exists(GEN_HEADER_PATH):
    os.remove(GEN_HEADER_PATH)
if path.exists(GEN_SOURCE_PATH):
    os.remove(GEN_SOURCE_PATH)

header_content = ''
source_content = ''

# parsing reports
registriesjson = json.load(open(path.join(REPORTS_DIR, 'registries.json')))
blockregistry = {key: v['protocol_id'] for key, v in registriesjson['minecraft:block']['entries'].items()}

blockjson = json.load(open(path.join(REPORTS_DIR, 'blocks.json')))

# generating data
block_type_enum_name = 'BlockTypes'
block_states_enum_name = 'BlockStates'
block_keys_strs = []
block_types_enum_data = []
block_states_enum_data = []
block_state_to_type_map_content = []
block_type_to_string_map_content = []
block_entries = 0
for key, block in blockjson.items():
    enum_name = str(key[len('minecraft:'):]).upper()

    block_keys_strs.append(f'char* __BLOCK_KEY_{enum_name} = (char*)"{key}";')
    block_type_to_string_map_content.append(
        f'{{ {block_type_enum_name}::{enum_name}, __BLOCK_KEY_{enum_name} }}'
    )
    block_types_enum_data.append(f'{enum_name} = {blockregistry[key]}') 
    
    for i in range(len(block['states'])):
        block_entries += 1
        gen_enum_name = enum_name
        if i > 0:
            gen_enum_name += f'_{i}'
            
        state = block['states'][i]
        block_states_enum_data.append(f'{gen_enum_name} = {state["id"]}')
        block_state_to_type_map_content.append(
            f'{{ ({block_states_enum_name}){state["id"]}, ({block_type_enum_name}){blockregistry[key]} }}'
        )

nl = '\n'
nlcomma = ',\n'
header_content += \
f"""
#define NUM_GLOBAL_BLOCK_ENTRIES {len(blockregistry)}
#define NUM_GLOBAL_BLOCK_STATE_ENTRIES {block_entries}

enum class {block_type_enum_name}
{{
{nlcomma.join(block_types_enum_data)}
}};

enum class {block_states_enum_name} {{
{nlcomma.join(block_states_enum_data)}
}};

extern {block_type_enum_name} block_type_from_state({block_states_enum_name} state);
extern std::string block_type_to_string({block_type_enum_name} type);
"""

source_content += \
f"""
{nl.join(block_keys_strs)}

std::map<{block_states_enum_name}, {block_type_enum_name}> BLOCK_STATE_TO_TYPE_MAP = {{ {nlcomma.join(block_state_to_type_map_content)} }};
std::map<{block_type_enum_name}, char*> BLOCK_TYPE_TO_STRING_MAP = {{ {nlcomma.join(block_type_to_string_map_content)} }};

{block_type_enum_name} block_type_from_state({block_states_enum_name} state)
{{
    return BLOCK_STATE_TO_TYPE_MAP[state];
}}

std::string block_type_to_string({block_type_enum_name} type)
{{
    return std::string(BLOCK_TYPE_TO_STRING_MAP[type]);
}}
"""


# write generated data
hfile = open(GEN_HEADER_PATH, 'w')
sfile = open(GEN_SOURCE_PATH, 'w')

hfile.write(f'''
#pragma once

{FILE_HEADER_COMMENT}

#include <string>

namespace minecraft
{{
{header_content}
}}
''')

sfile.write(f'''
{FILE_HEADER_COMMENT}

#include "generated.h"
#include <map>

namespace
{{
    struct __cmp_chr_ptr
    {{
        bool operator()(const char* a, const char* b) const
        {{
            return strcmp(a, b) < 0;
        }}
    }};
}}

namespace minecraft
{{

{source_content}

}}
''')