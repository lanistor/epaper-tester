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
