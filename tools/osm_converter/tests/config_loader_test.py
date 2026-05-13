import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent.parent / "src"))
from config_loader import ConfigLoader
import unittest

class TestConfigLoader(unittest.TestCase):
    def test_return_type(self):
        config = ConfigLoader.load_config("config.json")
        self.assertIsInstance(config, dict, "ConfigLoader should return a dict")
    
    def test_file_not_found_error(self):
        with self.assertRaises(FileNotFoundError):
            ConfigLoader.load_config("non_existent_file.json")
    
if __name__ == "__main__":
    unittest.main()