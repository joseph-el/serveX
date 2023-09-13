#!/bin/bash

SHELL_TYPE=$(basename $SHELL)

ALIAS_COMMAND="alias serveX='./serveX'"

case "$SHELL_TYPE" in
    "bash")
        CONFIG_FILE="$HOME/.bashrc"
        ;;
    "zsh")
        CONFIG_FILE="$HOME/.zshrc"
        ;;
    *)
        echo "Unsupported shell: $SHELL_TYPE"
        exit 1
        ;;
esac

echo "$ALIAS_COMMAND" >> "$CONFIG_FILE"
source "$CONFIG_FILE"
exec "$SHELL"
