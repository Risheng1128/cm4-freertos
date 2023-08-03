# cm4-freertos
A bare-metal project with FreeRTOS and SystemView on ARM Cortex-M4 processor.
- Device: [NUCLEO-F303ZE](https://www.st.com/en/evaluation-tools/nucleo-f303ze.html)

## Build
`cm4-freertos` dependents on some third-party packages to build code and burn into processor like [ARM GNU Toolchain](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain) and [stlink](https://github.com/stlink-org/stlink). Therefore, before using the project, we need to install these packages.

Install [ARM GNU Toolchain](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain):
```shell
$ sudo apt-get update
$ sudo apt-get -y install gcc-arm-none-eabi
```

Install [stlink](https://github.com/stlink-org/stlink):
```shell
$ sudo apt-get update
$ sudo apt-get -y install stlink-tools
```

Clone [FreeRTOS](https://github.com/FreeRTOS/FreeRTOS-Kernel), [SystemView](https://github.com/SEGGERMicro/SystemView.git) and [RTT](https://github.com/SEGGERMicro/RTT) as submodule:
```shell
$ git submodule update --init
```

Build `cm4-freertos`:
```shell
$ make
```

Burn the code into processor:
```shell
$ make upload
```
