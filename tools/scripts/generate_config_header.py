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

def write_out(header_content) -> None:
    output_path = Path(f"{project_root}/include/pathfind/generated_config.hpp")
    output_path.write_text(header_content)

def test_schema() -> bool:
    pass

def create_content() -> str:
    config = import_config()

    content = ""
    for section, values in config.items():
        for key, value in values.items():
            content += f"inline constexpr std::size_t {key} = {value};\n"

    return content

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