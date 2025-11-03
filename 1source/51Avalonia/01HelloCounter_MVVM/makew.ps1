$PROJNAME = "AvaloniaApplication2"
$PUBLISHDIR = ".\PUBLISHED"

$paths = $PUBLISHDIR, ".\${PROJNAME}\bin\Release\net9.0\win-x64"
Get-Item -LiteralPath $paths -ErrorAction SilentlyContinue | Remove-Item -Recurse

dotnet publish .\$PROJNAME\$PROJNAME.csproj --runtime win-x64 --no-self-contained --output $PUBLISHDIR
