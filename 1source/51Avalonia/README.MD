# Avalonia

* `00HelloCounter_CodeBehind` – HelloCounter (simple counter project for understanding the basic principles of the imgui paradigm (and the difference compared to rmgui)); uses the "code behind" approach
* `01HelloCounter_Independent` – HelloCounter; uses the "MVVM" approach

## Running Avalonia

### Windows 10 22H2

* Prerequisite: [.NET 9 SDK](https://dotnet.microsoft.com/en-us/download/dotnet/9.0)

```powershell
# Navigate to project folder
cd <path_to_this_repository>\1source\51Avalonia\00HelloCounter_CodeBehind

# Build
.\makew.ps1

# Run
.\PUBLISHED\AvaloniaApplication1.exe
```

### Linux Debian 13.1 KDE Plasma

```bash
# Install .NET 9 SDK
wget https://packages.microsoft.com/config/debian/12/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
sudo dpkg -i packages-microsoft-prod.deb
rm packages-microsoft-prod.deb
sudo apt-get update && sudo apt-get install -y dotnet-sdk-9.0

# Navigate to project folder
cd <path_to_this_repository>/1source/51Avalonia/00HelloCounter_CodeBehind

# Build
make

# Run
./PUBLISHED/AvaloniaApplication1
```
