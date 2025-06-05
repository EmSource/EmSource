#!/bin/bash

LLVM_OBJCOPY=$(which llvm-objcopy)
EMAR=$(which emar)

function usage {
    echo "$0 /path/to/input/file [-o /path/to/output/file ]"
    echo ""
}

if [ $# == 0 ]; then
    usage
    exit 2
fi

if [ $(basename "$1") == "$1" ]; then
    INFILEDIR=$PWD
else
    INFILEDIR=$(cd "${1%/*}" && echo $PWD)
fi
INFILE=$(basename "$1")

OUTFILEDIR=$INFILEDIR
OUTFILE=$INFILE.dbg

shift
while getopts "o:" opt; do
    case $opt in
        o)
            OUTFILEDIR=$(cd "${OPTARG%/*}" && echo $PWD)
            OUTFILE=$(basename "$OPTARG")
            ;;
    esac
done

if [ "$OUTFILEDIR" != "$INFILEDIR" ]; then
    INFILE=${INFILEDIR}/${INFILE}
    OUTFILE=${OUTFILEDIR}/${OUTFILE}
fi

FILETYPE=$(file "$INFILE")
if echo "$FILETYPE" | grep -q "WebAssembly"; then
    echo "[gendbg.sh] Handling WebAssembly object archive"
    $LLVM_OBJCOPY --only-keep-debug "$INFILE" "$OUTFILE"
    $LLVM_OBJCOPY --strip-debug "$INFILE"
    $LLVM_OBJCOPY --add-gnu-debuglink="$OUTFILE" "$INFILE"
    exit 0
fi

if [[ "$INFILE" == *.a ]]; then
    echo "[gendbg.sh] Rebuilding archive $INFILE"
    TMPDIR=$(mktemp -d)
    INFILE_ABS=$(realpath "$INFILE")
    pushd "$TMPDIR" >/dev/null
    $EMAR x "$INFILE_ABS"
    OBJFILES=(*.o)

    if [ ${#OBJFILES[@]} -eq 0 ]; then
        echo "[gendbg.sh] Error: No object files found in archive."
        echo "Contents of $TMPDIR:"
        ls -l
        popd >/dev/null
        rm -rf "$TMPDIR"
        exit 1
    fi

    $EMAR rcs "$OUTFILE" "${OBJFILES[@]}"
    popd >/dev/null
    rm -rf "$TMPDIR"
    exit 0
fi

pushd "$INFILEDIR" >/dev/null
$LLVM_OBJCOPY --only-keep-debug "$INFILE" "$OUTFILE"
$LLVM_OBJCOPY --strip-debug "$INFILE"
$LLVM_OBJCOPY --add-gnu-debuglink="$OUTFILE" "$INFILE"
popd >/dev/null
