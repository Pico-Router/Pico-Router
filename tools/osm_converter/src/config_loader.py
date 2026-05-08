import json
import pathlib

class ConfigLoader:
    """
    Handles fetching and parsing of JSON configuration file
    """
    @classmethod
    def load_config(cls, config_name: str) -> dict:
        current_path = pathlib.Path(__file__).parent.resolve()
        project_root = None
        for parent in current_path.parents:
            if parent.name == "pico-router":
                project_root = parent
                break
        
        if project_root is None:
            raise RuntimeError("Could not find 'pico-router' root directory.")

        config_path = project_root / config_name

        with open(config_path, 'r') as f:
            return json.load(f)