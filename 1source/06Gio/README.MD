# Gio

## Running Gio

### Windows

* [Download](https://go.dev/dl/) and install Go

```powershell
# Install all the dependencies
go install gioui.org/cmd/gogio@latest

# Navigate to sample project, update all the dependencies, and run the program
cd ...\1source\6Gio\00SampleProject
go mod tidy
go run .
```

### Linux

```bash
# Download and untar Go from https://go.dev/dl/

# "Install"
sudo mv ./go /usr/local
export PATH=$PATH:/usr/local/go/bin
go version # check if Go is working

# Install all the dependencies
go install gioui.org/cmd/gogio@latest
sudo apt install gcc pkg-config libwayland-dev libx11-dev libx11-xcb-dev libxkbcommon-x11-dev libgles2-mesa-dev libegl1-mesa-dev libffi-dev libxcursor-dev libvulkan-dev

# Navigate to sample project, update all the dependencies, and run the program
cd .../1source/6Gio/00SampleProject
go mod tidy
go run .
```
