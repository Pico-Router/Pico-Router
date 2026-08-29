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
    echo
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

    if ! git -C "$dir" rev-parse --is-inside-work-tree >/dev/null 2>&1; then
        echo "Error: expected Git repository missing: $dir"
        exit 1
    fi
done

echo "==> Applying patches to Renode_RP2040..."

PATCH_DIR="$REPO_ROOT/patches/Renode_RP2040"
TARGET_DIR="$REPO_ROOT/third_party/Renode_RP2040"

if [[ -d "$PATCH_DIR" ]]; then
    shopt -s nullglob

    for patch_file in "$PATCH_DIR"/*.patch; do
        echo "==> Processing $(basename "$patch_file")"

        if git -C "$TARGET_DIR" apply --check "$patch_file"; then
            echo "    Applying..."
            git -C "$TARGET_DIR" apply "$patch_file"
            echo "    Applied."

        elif git -C "$TARGET_DIR" apply \
            --reverse \
            --check \
            "$patch_file"; then

            echo "    Already applied."

        else
            echo "Error: patch is neither applicable nor already applied:"
            echo "  $patch_file"
            echo
            echo "Submodule status:"
            git -C "$TARGET_DIR" status --short
            exit 1
        fi
    done

    shopt -u nullglob
else
    echo "==> No patch directory found, skipping."
fi

echo "==> Building devcontainer..."

devcontainer build \
    --workspace-folder "$REPO_ROOT" \
    --no-cache

echo
echo "========================================"
echo " Devcontainer build complete!"
echo "========================================"