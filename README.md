# Epdiy tester

## Clone

```bash
git clone git@github.com:lanistor/epaper-tester.git
cd epaper-tester
git submodule update --init --recursive
```

## Start test

```bash
idf.py build flash monitor -p [port]
```

## For windows development

Please delete `components/epd_driver`, and then copy `packages/epdiy/src/epd_driver` to `components/epd_driver`.

## For simulator

```bash
cd simulator
make -j 16
```

Then use vscode - `debug` - `Simulator Run`.

## Folder description

**The connector of epdiy-lvgl**

- `components/lvgl_epaper_drivers/lvgl_tft/epdiy_epaper.cpp`
  - the core function is `epdiy_repaint`

**The test view code**

- `main/modules/tester/pack/index.cpp`
