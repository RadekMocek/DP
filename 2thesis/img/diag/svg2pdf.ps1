$filenames = @(
    "err_high"
    "m_canvas_nodes"
    "wireframe"
)

$filenames | ForEach-Object {
    & "C:\_Programy\Inkscape\bin\inkscape.exe" --export-type=pdf "${_}.svg"
}
