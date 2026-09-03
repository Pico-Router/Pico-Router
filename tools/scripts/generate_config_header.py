import re
import sys
import json
from pathlib import Path

project_root = Path(__file__).resolve().parents[2]

def import_config() -> dict:
    config_path = project_root / "config.json"

    try:
        with config_path.open() as f:
            config = json.load(f)
        return config
    except FileNotFoundError:
        print(f"{config_path} was not found")
        return {}
    except json.JSONDecodeError:
        print(f"{config_path} contains invalid JSON")
        return {}

def write_out(header_content: str) -> None:
    output_path = Path(f"{project_root}/include/pathfind/generated_config.hpp")
    output_path.write_text(header_content)

def schema_is_valid(config: dict) -> bool:
    required_keys = [
        "MAX_NODES",
        "MAX_EDGES",
        "MAX_PATH_LENGTH"
    ]

    if not isinstance(config, dict) or not config:
        print("Schema Error: Config is missing or not a top-level JSON object.")
        return False

    identifier_regex = re.compile(r"^[a-zA-Z_][a-zA-Z0-9_]*$")
    found_required_keys = set()

    for section, values in config.items():
        if not isinstance(values, dict):
            print(f"Schema Error: Section '{section}' must be an object/dict.")
            return False

        for key, value in values.items():
            if not isinstance(key, str) or not identifier_regex.match(key):
                print(f"Schema Error: Key '{key}' in section '{section}' is not a valid C++ identifier.")
                return False
            if not isinstance(value, int) or isinstance(value, bool) or value < 0:
                print(f"Schema Error: Value for '{key}' in section '{section}' must be a non-negative integer.")
                return False
            if key in required_keys:
                found_required_keys.add(key)

    missing_keys = set(required_keys) - found_required_keys
    if missing_keys:
        print(f"Schema Error: Missing required keys: {', '.join(missing_keys)}")
        return False

    return True

def create_content() -> str:
    config = import_config()

    if schema_is_valid(config):
        content = ""
        for section, values in config.items():
            for key, value in values.items():
                content += f"inline constexpr std::size_t {key} = {value};\n"
        return content
    else:
        print("Failed to write include/pathfind/generated_config.hpp!")
        sys.exit(1)

template_content = create_content()

base_template = f"""
#pragma once

/**
This file was auto generated. Do not edit.
*/

#include <cstddef>

namespace pathfind::config {{

{template_content}
}}
"""

write_out(base_template)

print("Done writing include/pathfind/generated_config.hpp!")