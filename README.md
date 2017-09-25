# vermiliad
dsp &amp; controlled voltage
數位訊號處理 & 控制電壓

## 繁體中文:

始於2015年末的碩士論文題目「以Raspberry Pi、Python和Pure Data為基礎建造開源模組化合成器」，在麻豆當兵期間，不斷的實作與開發，將許多硬體和軟體的部分做了更有效率的調整與升級，並將模組的定位限制在real time dsp，使用者能夠在pure data上客製自己的模組功能，筆者也在pure data上實作了miller puckette的feedback delay network reverb，也有不錯的回饋。最後，透過開源的方式來管理這個專案，希望能帶給開源社群與合成器社團更多貢獻，以下將介紹本模組的特色與修改項目。

軟體方面筆者尚未找到比udp介面更適合傳輸資料到pure data的方法，所以沿用在舊版論文中的架構，透過mcp3008取得外部控制電壓的參數後，利用python傳送到udp網路即可被pure data讀取，但在python使用迴圈傳送資料會造成大量記憶體的消耗，筆者也曾使用linux bash的方式來進行迴圈，但結果依然不盡理想，0.5毫秒的傳輸頻率會消耗25%的cpu與18%的記憶體。python腳本會隨著raspberry pi與其他不穩定的因素在使用上能察覺外部控制的延遲，另外一點也是python本身是直譯式語言，雖然有很多方法能讓執行的速度和效率能在更高一點，但更換語言會是更好的選擇。

最後筆者改使用c++取代python當作mcp3008與raspberry pi溝通的介面，而結果也十分顯著，取樣速度能到達0.1毫秒甚至更低，記憶體使用率約在3%以下與cpu佔用率也在5%左右，在使用上有更順暢的操控性，另外也能供給更多資源給pure data。

硬體方面使用了i2s的音訊傳輸介面取代舊版的usb audio，晶片選用許多模組廠商已經成熟使用的wm8731，在linux kernel升級成4.4之後驅動模組也內建在kernel裡了，開發者能免除cross compiling的困擾，音質也有顯著的提升。在外部的控制電壓迴路上，設計op amp迴路調整電壓區間至mcp3008可接受的範圍，也將音源外部輸出做了很大的變更，音源原始訊號會與codec輸出訊號混合，使用vactrol控制乾濕訊號混合的比例，取代許多dsp類型的效果器是在數位迴路中做乾濕訊號混合的控制。

layout部分被拆成兩個電路板，adapter作為audio io與analog io，另外motherboard作為擴充，如調整電壓至modular level、vactrol mixing、cv adjustment…

後記：
很可惜pure data的主程式已經不再更新了，在操縱模式介面都沒什麼改變的情況下，每次更新大多鎖定在平台擴充和臭蟲的清理、新增特定的library...等等，在新型平台趨近穩定的狀況，如:raspberry pi、beaglebone...加上多種library與功能的完善，主程式的更新其實越來越沒必要性，新的plugin deken會是一個不錯的走向，作為管理和新增library很重要的幫手。

## English:
under construction
