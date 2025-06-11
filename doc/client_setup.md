# 3.4 Setting up the client
This is the final step — you're almost there!

We now need to make sure the client is configured to connect to your local server.

### Download the client
You can use any client version newer than Surge, but I personally recommend the ToyBattles client. Here are the download links:
- Mediafire: https://www.mediafire.com/file/4flrsczyh74a0yi/ToyBattles.zip/file
- Google Drive: https://drive.google.com/file/d/1hTLwJy3JDajafw8ogdEIM-obCFnR2_Zq/view

### Install the `cgd.dip` archive with localhost IPs
Next, download the latest cgd.dip archive from the link below. This file is already set up to point to 127.0.0.1 (localhost) and includes all necessary client data: https://www.mediafire.com/file/5uw65fwps66fsll/cgd.dip/file

This will allow your client to connect to your localhost (127.0.0.1) server.

✅ Note: This archive is pre-configured to work with the provided config.ini file. You don’t need to change the ports — everything should match up automatically.

When done, make sure to replace the `cgd.dip` you have in your game folder / `data` with this one. (Take a backup of the original one just in case)

### Start the client
To launch the game, you have two options:

- Run the _Launcher.bat script, or
- Open the client folder, go to /Bin, and run either MicroVolts.exe or ToyBattles.exe, depending on the client version you downloaded.

# Final Checklist: Starting Everything Up
By now, you should have completed the following steps:
- ✅ Compiled all the executables (Common, MainServer, AuthServer, and CastServer)
- ✅ Launched each server executable without seeing any red error messages
- ✅ Set up and started your MariaDB database
- ✅ Edited your config.ini file so that all IPs point to 127.0.0.1 (localhost), if you're using the cgd.dip file from above
- ✅ Downloaded and started the client

If everything’s in place and running correctly, you should be able to log in using the following test credentials:

Username: test
Password: test


## Next
[4.1 Config setup for localhost](https://github.com/SoWeBegin/MicrovoltsEmulator/blob/mv1.1_2.0/doc/example_localhost.md)
