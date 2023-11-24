# Vermiliad - An open-source hardware solution for building digital modular synthesizers
* DSP, Pure Data, and Controlled Voltage in a single pcb!
* 數位訊號處理、Pure Data、控制電壓融合在在一塊小小的PCB！

<img src="https://user-images.githubusercontent.com/15021145/285414660-69b3eb3e-63e6-4aa7-8fcb-ff2c81d1cf1e.JPG" width="480">

## DEMO:

<video src='https://github-production-user-asset-6210df.s3.amazonaws.com/15021145/285418308-6633f0b2-d7b3-4ce2-ba0a-d69b2f7387a2.mp4' width=180/>
  
<video src='https://github-production-user-asset-6210df.s3.amazonaws.com/15021145/285418398-cd53d4ac-97a0-486a-81fa-60b1c6fd6b72.mp4' width=180/>

## PCB Layout:

* Top Of Adapter
<img src="https://user-images.githubusercontent.com/15021145/30796960-cd4b5b22-a206-11e7-84ff-6005570c5a67.png" width="280">

* Bottom Of Adapter
<img src="https://user-images.githubusercontent.com/15021145/30796958-cd006d7e-a206-11e7-9c64-897f3f4fd79b.png" width="280">

* Top Of Motherboard
<img src="https://user-images.githubusercontent.com/15021145/30796961-ce5ef316-a206-11e7-9a36-1bf88692054d.png" width="480">

* Bottom Of Motherboard
<img src="https://user-images.githubusercontent.com/15021145/30796962-ce5f92e4-a206-11e7-8839-7095d0f902c5.png" width="480">

## Introduction:

This article introduces the master's thesis titled "Building an Open Source Modular Synthesizer Based on the Integration of Raspberry Pi, Python and Pure Data." initiated in late 2015. During my military service in Madou, Tainan, I continuously worked on and developed this project, efficiently adjusting and upgrading various hardware and software components. This module is designed for Real-Time DSP, allowing users to customize modular synthesizer functions on Pure Data. I also implemented Miller Puckette's Feedback Delay Network Reverb on Pure Data, receiving positive feedback. The project is ultimately managed as an open-source initiative, aiming to contribute more to the open-source community and synthesizer enthusiasts.

In terms of software, I found no better method than the UDP interface for transmitting data to Pure Data. I used MCP3008 to receive external control voltage parameters, then transmitted them to the UDP network via Python for Pure Data to read. However, Python's looped data transmission consumed significant memory. Even attempts using Linux Bash loops were unsatisfactory, as a 0.5-millisecond transmission frequency consumed 25% of the CPU and 18% of the memory. Python scripts were affected by Raspberry Pi and other unstable factors, leading to external control delays. Given that Python is an interpreted language, despite methods to improve performance, switching languages proved to be a better option.

Ultimately, I replaced Python with C++ as the interface for communication between MCP3008 and Raspberry Pi. This led to significant improvements: the sampling speed could reach 0.1 milliseconds or even faster, with about 3% memory usage and approximately 5% CPU occupancy. This change enhanced the operation smoothness and provided more resources for processing audio inside Pure Data.

In hardware, I used the I2S audio transmission interface instead of the previous USB Audio, choosing the WM8731 chip, widely used by many module manufacturers. After upgrading the Linux kernel to 4.4, the I2S driver module was built into the kernel, relieving developers from the hassle of cross-compiling and significantly improving sound quality. The external control voltage circuit was designed with an OP Amp to adjust the voltage range to meet MCP3008's requirements. Major changes were made to the external output of the sound source, mixing the original signal with the Codec output, and using Vactrol to control the dry/wet signal ratio, replacing many DSP-type effects in digital loop control.

The board layout was divided into two parts: the Adapter responsible for Audio I/O and Analog I/O, and the Motherboard for expansion, such as adjusting voltage to Eurorack Level, Vactrol Mixing, CV Adjustment, etc.

## Epilogue:

Regarding the development of Pure Data, it is regrettable that the main program is no longer updated. The interface and editor has hardly changed, and updates mainly focus on platform expansion, bug fixes, and adding specific libraries. With the stabilization of new platforms like Raspberry Pi and BeagleBone, and the improvement of various libraries and functions, the frequency of updates to the main program has gradually decreased. The new Deken Plugin will become an important tool for managing and adding libraries.

## 簡介:

本文介紹的碩士論文題目「基於Raspberry Pi、Python和Pure Data構建開源模組化合成器」始於2015年底。在服役於台南麻豆期間，我持續實作與開發，對許多硬體與軟體部分進行高效調整和升級。此模組是為了服務Real-Time DSP，允許使用者在Pure Data上自定義模組合成器功能。我還在Pure Data上實現了Miller Puckette的Feedback Delay Network的Reverb，獲得良好回饋。該項目最終以開源方式管理，旨在為開源社區和合成器愛好者貢獻更多。

在軟體方面，我未找到比UDP介面更合適的方法將數據傳輸到Pure Data。我使用MCP3008接收外部控制電壓參數，再通過Python傳輸至UDP網路供Pure Data讀取。然而，Python循環傳輸資料會大量消耗記憶體。即使嘗試過Linux Bash進行循環，結果仍不理想，0.5毫秒的傳輸頻率會消耗25%的CPU和18%的記憶體。Python腳本受Raspberry Pi和其他不穩定因素影響，導致外部控制延遲。鑑於Python是直譯式語言，儘管有提高效能的方法，更換語言仍是更佳選擇。

最終，我改用C++取代Python作為MCP3008與Raspberry Pi的通訊介面。這帶來顯著改善，取樣速度可達0.1毫秒甚至更快，記憶體使用率約3%，CPU佔用率約5%，使操作更加順暢，並為Pure Data提供更多資源。

在硬體方面，我採用I2S音訊傳輸介面取代舊有的USB Audio，選用WM8731晶片，該晶片已被許多模組製造商廣泛使用。Linux kernel升級至4.4後，驅動模組內建於kernel中，開發者無需煩惱cross-compiling，音質也顯著提升。外部控制電壓迴路設計了OP Amp迴路以調整電壓範圍，符合MCP3008的要求，並對音源外部輸出進行重大改動，原始訊號與Codec輸出訊號混合，使用Vactrol控制乾濕訊號比例，替代了許多DSP類型效果器在數位迴路中的控制。

板子布局被分為兩部分：Adapter負責Audio I/O和Analog I/O，Motherboard則用於擴充，例如調整電壓至Eurorack Level、Vactrol Mixing、CV Adjustment等。

## 後記：
在Pure Data的發展上，遺憾的是主程式已不再更新。操控模式介面幾無變化，更新主要針對平台擴充、臭蟲修復和新增特定Library等。隨著新型平台如Raspberry Pi、BeagleBone的穩定，以及多種Library和功能的完善，主程式的更新逐漸減少。新的Deken Plugin將成為管理和新增Library的重要工具。
