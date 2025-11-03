PROJNAME="AvaloniaApplication2"
PUBLISHDIR="./PUBLISHED"

publish:
	dotnet publish ./$(PROJNAME)/$(PROJNAME).csproj --runtime linux-x64 --no-self-contained --output $(PUBLISHDIR)

clean:
	rm -rf ./$(PROJNAME)/bin/Release/net9.0/linux-x64
	rm -rf $(PUBLISHDIR)