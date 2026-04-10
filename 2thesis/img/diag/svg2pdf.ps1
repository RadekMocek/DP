$filenames = @(
    "err_high"
    "wireframe"
)

$filenames | ForEach-Object {
    & "C:\_Programy\Inkscape\bin\inkscape.exe" --export-type=pdf "${_}.svg"
}
