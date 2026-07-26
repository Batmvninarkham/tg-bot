# build tgcpp library from source  
- download the original tgcpp repo  
- your layout should look like this   
 ```
~/tgbot/  
├── bot/  
│   ├── CMakeLists.txt  
│   └── src/  
└── tgbot-cpp-master/  
    ├── CMakeLists.txt  
        └── include/
     ```  
> in your bot build dir  

```
cmake ..  
cmake --build . 
```
> env variables needed are :
- userid of the owner of the bot 
- chatid of any group you wnat to administer
