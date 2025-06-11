# 2.1 Changelog from version 1.0 to version 2.0

A lot of things changed and the list is simply too big to fit in a page. I will try to focus on the most important aspects to give an idea how much work was put in the last year (thanks to the community who helped testing too, of course!)

## 2.1.1 Complete code refactoring
The whole code base (Main, cast, auth servers and Common) were refactored. Version 1.0 had a lot of issues regarding mantainability, code readibility and lifetime issues related to how ASIO things were handled.

### Code organization & readibility
Version 2.0 provides a much better organized and readable code. This makes newcomers experience easier to grasp the whole code base, as the logic in version 1.0 was **really** too complicated.

### Networking performance
Version 2.0 offers better networking performance with ASIO. Also, most of the server handlers & session management was rewritten with optimization in mind. Many data strucutres were changed:
- used the stack where possibly instead of allocating memory.
- flattened multiple arrays.
- Made the logic much better server side for quicker code execution.

### Security improvements & server stability
The new version also had security improvements in mind.
- Multiple exploits prevention are now available in this version: prevented various exploits such as room crashes, duplicate items, items disappearing, etc.
- Anti-SYS flooding system: there were issues with SYS flooding in the ToyBattles project. I thus decided to add a simple anti SYS flooding system.
- No more constant server crashes: a lot of issues related to bad memory management were fixed. The servers in version 2.0 are now much, much more stable and with less crashes than ever!
- Added 2FA authentication for graded accounts (mandatory), and for normal accounts (if wanted).
  
### Bug fixes
Almost all bugs that existed in version 1.0 were fixed:
- Automatic host change bugs that crashed the server or the room were solved,
- Multiple bugs related items disappearing were fixed,
- Multiple inventory-related bugs were fixed,
- Trade system bugs were fixed.
- Match related bugs were mostly fixed.
- Infinite match loading is now fixed.
- The mail notifications now disappear after retrieving a gift.
- In-game messages are now handled properly.
- The "2 nades/bazooka simultaneously" bug is now fixed.
- The lucky meter free spin in the capsule that caused client crashes before is fixed.
- Single wave end screen is now working properly.
- Room settings are now always updated correctly.
- Host suicide in-match now works properly.
- No more ping related issues inside matches.
- Death chat now works correctly.
- Fixed various room join player-duplication bugs.
 ...and much more!

## 2.1.2 New Features
I also added a lot of new features in version 2.0!
- Arena Mode: this is a mode inspired by ToyHeroes, but fully server sided in this project. To enable it, all you need is to be in a room with the "Academy Training Ground" map. You can find examples of Arena Mode on youtube.
- Assassin Mode: this is a completely new, server-sided mode. It works on Elimination and can be activated while you're the host in a room by using the chat command `/setassassinmode`. Make sure to try it out!
- Gift System was now added. Game masters can use the `/sendgift` command to send items to players.
- New in-game commands for Event Supporters, Moderators and Game Masters: these can be all found inside MainServer/ChatCommands.
- Improved the Trade System.
- Clan wars finally work!
- Event missions were introduced. These must be enabled inside the main server (MainServer/include/handlers/HandleEliminationNextRound.h) and by modifying the `cdb.dip` archive.
- Level up rewards are now available.
- Level up now works correctly.
- Clan icons are now displayed correctly in all rooms.
- In-game battery is now given correctly.
- Multiple items addition: instant respawn for matches, boxes, battery boxes, super glues, etc.
- Inventory enhancements: weapon upgrades, items for upgrading etc. now work correctly without a relog.
- Tutorial and single wave now gives reward boxes as originally.
- It is now possible to votekick during a match.
- Random map selection now works properly.
- Added weekly & monthly rewards. 
- Multiple servers across different VPS are now handled correctly and you can set them up easily.
- Added a `config.ini` file to keep track of the setup and all the servers.
- Coupons and coupon shop now work properly.
- The main server can now handle requests from your admin panel (a website). You can now send commands to the main server externally!
- Achievements were implemented and are now stored in the database.
- Added capsule sale events, event missions start and end dates inside the database. The trade system can now be enabled by date as well.
 ...and so much more!

## 2.1.3 Database changes
Version 1.0 used SQLite. The new version 2.0 now uses MariaDB, which is much more flexible and serious for this project. 

This means that the whole database operations were all refactored. And it also means that multiple servers can now use the same database!

## 2.1.4 Client Updater
In version 2.0 I also decided to make the client updater open source. This means that you're now able to use this updater to force everyone to update their client with the latest content that you decide.
