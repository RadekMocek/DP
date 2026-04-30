$filenames = @(
    "err_high"
    "m_canvas_nodes"
    "slider"
    "wireframe"
)

$filenames | ForEach-Object {
    & "C:\_Programy\Inkscape\bin\inkscape.exe" --export-type=pdf "${_}.svg"
}
