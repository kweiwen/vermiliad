# vermiliad
* DSP, Pure Data &amp; Controlled Voltage
* 數位訊號處理, pure data & 控制電壓

## PCB Layout:

* top of adapter
<img src="https://user-images.githubusercontent.com/15021145/30796960-cd4b5b22-a206-11e7-84ff-6005570c5a67.png" width="280">

* bottom of adapter
<img src="https://user-images.githubusercontent.com/15021145/30796958-cd006d7e-a206-11e7-9c64-897f3f4fd79b.png" width="280">

* top of motherboard
<img src="https://user-images.githubusercontent.com/15021145/30796961-ce5ef316-a206-11e7-9a36-1bf88692054d.png" width="480">

* bottom of motherboard
<img src="https://user-images.githubusercontent.com/15021145/30796962-ce5f92e4-a206-11e7-8839-7095d0f902c5.png" width="480">

## 繁體中文:

本文介紹的碩士論文題目「基於Raspberry Pi、Python和Pure Data構建開源模組化合成器」始於2015年底。在服役於麻豆期間，我持續實作與開發，對許多硬體與軟體部分進行高效調整和升級。此模組限定於real-time dsp，允許使用者在Pure Data上自定義模組功能。我還在Pure Data上實現了Miller Puckette的feedback delay network reverb，獲得良好回饋。該項目最終以開源方式管理，旨在為開源社區和合成器愛好者貢獻更多。

在軟體方面，我未找到比UDP介面更合適的方法將數據傳輸到Pure Data。我使用MCP3008接收外部控制電壓參數，再通過Python傳輸至UDP網路供Pure Data讀取。然而，Python循環傳輸資料會大量消耗記憶體。即使嘗試過Linux Bash進行循環，結果仍不理想，0.5毫秒的傳輸頻率會消耗25%的CPU和18%的記憶體。Python腳本受Raspberry Pi和其他不穩定因素影響，導致外部控制延遲。鑑於Python是直譯式語言，儘管有提高效能的方法，更換語言仍是更佳選擇。

最終，我改用C++取代Python作為MCP3008與Raspberry Pi的通訊介面。這帶來顯著改善，取樣速度可達0.1毫秒甚至更快，記憶體使用率約3%，CPU佔用率約5%，使操作更加順暢，並為Pure Data提供更多資源。

在硬體方面，我採用I2S音訊傳輸介面取代舊有的USB audio，選用WM8731晶片，該晶片已被許多模組製造商廣泛使用。Linux kernel升級至4.4後，驅動模組內建於kernel中，開發者無需煩惱cross compiling，音質也顯著提升。外部控制電壓迴路設計了op amp迴路以調整電壓範圍，符合MCP3008的要求，並對音源外部輸出進行重大改動，原始訊號與codec輸出訊號混合，使用vactrol控制乾濕訊號比例，替代了許多dsp類型效果器在數位迴路中的控制。

板子布局被分為兩部分：adapter負責audio I/O和analog I/O，motherboard則用於擴充，例如調整電壓至modular level、vactrol mixing、CV adjustment等。

## 後記：
在Pure Data的發展上，遺憾的是主程式已不再更新。操控模式介面幾無變化，更新主要針對平台擴充、臭蟲修復和新增特定library等。隨著新型平台如Raspberry Pi、BeagleBone的穩定，以及多種library和功能的完善，主程式的更新逐漸減少。新的Deken Plugin將成為管理和新增library的重要工具。

## English:
under construction
