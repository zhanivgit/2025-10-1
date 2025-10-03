# Copilot Instructions for STM32-Hal Project

## 项目架构概览
- 本项目为 STM32F1 系列单片机的固件工程，采用 HAL 库驱动，主要分为如下模块：
  - `Core/Inc` & `Core/Src`：主程序入口、外设初始化与中断服务。
  - `Drivers/MCU`：自定义外设驱动（如蜂鸣器、LED、光敏传感器、OLED 显示、循迹模块）。
  - `Drivers/STM32F1xx_HAL_Driver` & `Drivers/CMSIS`：官方 HAL 库与底层 ARM CMSIS 支持。
  - `MDK-ARM/`：Keil 工程文件、启动文件、编译输出（.hex/.map/.axf 等）。

## 关键开发流程
- **编译/烧录**：
  - 使用 Keil MDK-ARM (`STM32-Hal.uvprojx`) 进行编译与调试。
  - 编译输出在 `MDK-ARM/STM32-Hal/`，如 `STM32-Hal.hex` 用于烧录。
- **代码入口**：
  - 主函数在 `Core/Src/main.c`，初始化流程、主循环均在此实现。
  - 外设初始化函数通常在 `Core/Src/tim.c`、`Core/Src/gpio.c` 等。
- **中断与回调**：
  - 所有中断服务例程在 `Core/Src/stm32f1xx_it.c`。
  - HAL 回调函数可在 `Core/Src/stm32f1xx_hal_msp.c` 扩展。

## 项目约定与模式
- **自定义驱动**：
  - 新增外设驱动请放在 `Drivers/MCU/`，头文件与源文件同名。
  - 例如：`Led.c`/`Led.h`、`OLED.c`/`OLED.h`。
- **命名规范**：
  - 变量、函数名采用小写加下划线或驼峰，保持与 HAL 库风格一致。
- **配置文件**：
  - `STM32-Hal.ioc` 为 CubeMX 工程配置文件，外设映射、引脚分配等均在此维护。

## 重要文件参考
- `Core/Src/main.c`：主入口，系统初始化与主循环。
- `Core/Src/stm32f1xx_it.c`：中断服务例程。
- `Drivers/MCU/`：自定义硬件驱动实现。
- `STM32-Hal.ioc`：CubeMX 配置。
- `MDK-ARM/STM32-Hal.uvprojx`：Keil 工程。

## 典型模式示例
- **外设初始化**：
  - 在 `main.c` 调用 `MX_GPIO_Init()`、`MX_TIMx_Init()` 等。
- **自定义驱动调用**：
  - 例如：`Led_On()`、`Buzzer_Play()`，在主循环或中断中调用。
- **中断处理**：
  - 在 `stm32f1xx_it.c` 中实现定时器、外部中断等服务。

## 其他说明
- 本项目未包含自动化测试脚本，调试流程依赖 Keil IDE。
- 若需扩展新硬件模块，建议先在 CubeMX (`STM32-Hal.ioc`) 配置，再补充驱动代码。

---
如需补充特殊约定或遇到不明确的结构，请在此文件补充说明。