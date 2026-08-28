set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

cd "$REPO_ROOT"

command -v git >/dev/null 2>&1 || {
    echo "Error: git is required but was not found."
    exit 1
}

command -v devcontainer >/dev/null 2>&1 || {
    echo "Error: devcontainer CLI is required but was not found."
    echo "Install it with:"
    echo "  npm install -g @devcontainers/cli"
    exit 1
}

echo "==> Repository: $REPO_ROOT"

echo "==> Syncing Git submodules..."
git submodule sync --recursive

echo "==> Initializing Git submodules..."
git submodule update --init --recursive

echo "==> Verifying submodules..."

for dir in \
    third_party/Renode_RP2040 \
    third_party/Renode_RP2040_PioSim
do
    if [[ ! -d "$dir" ]]; then
        echo "Error: expected submodule missing: $dir"
        exit 1
    fi
done

echo "==> Building devcontainer..."

devcontainer build --workspace-folder "$REPO_ROOT" --no-cache

echo
echo "========================================"
echo " Devcontainer build complete!"
echo "========================================"