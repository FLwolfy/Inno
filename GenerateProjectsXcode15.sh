chmod +x "$0"

cd "$(cd "$(dirname "$0")" && pwd)"
.premake/Macosx/premake5 xcode4

exit 0