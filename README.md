# Bedrock Server Manager

This project is inteded to design a program that will allow multiple Minecraft Bedrock servers to run on a single computer and select which server to access at runtime. 

Built and tested on WSL: Ubuntu 18.04


## To begin working:

### Install the Windows Subsystem for Linux

1. Search for "windows features" on your PC

![](images/windows_features_search.png)

2. Scroll until you find the option "Windows Subsytem for Linux"

![](images/windows_features_open.png)

3. Click the check mark, click ok, and restart.


### Install Ubuntu 18.04 from the Windows Store

Once downloaded, open it and follow the setup instructions. 
Note: Ubuntu will start you in a directory called "/home/[username]". You can access the C: drive using the command "cd /mnt/c".

### Clone the git repository

If you don't have git, run the following commands in Ubuntu 18.04


    sudo apt install git

    git clone https://github.com/zday294/Bedrock_Server_Manager.git 
    

You should now have the repository available in Ubuntu 18.04. If you're unfamiliar with git and github, read gitting_started.md
