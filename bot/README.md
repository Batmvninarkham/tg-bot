# build tgcpp library from source
- download the original tgcpp repo 
- your layout should look like this 
`~/tgbot/
├── bot/
│   ├── CMakeLists.txt
│   └── src/
└── tgbot-cpp-master/
    ├── CMakeLists.txt
        └── include/`
> in your bot build dir
`cmake ..
cmake --build .`


