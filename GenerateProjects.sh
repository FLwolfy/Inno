#!/bin/bash

chmod +x "$0"

cd "$(cd "$(dirname "$0")" && pwd)"

echo "Enter the IDE to generate:"
read IDE_NAME

.premake/Macosx/premake5 "$IDE_NAME"

exit 0