# m5stack_co2

CO2 monitor on M5stack

## Devises

- M5stack basic
- MHZ-19B

### Connection

| M5stack | MHZ-19B |
| ------- | ------- |
| 5V      | Vin     |
| GND     | GND     |
| R2      | TX      |
| T2      | RX      |


## Feature

### CO2 logging

LCD displays the moving average CO2 data(ppm) of last 16 data par minuit. Function of communication MHZ-19B is based on follow.

[オフィス換気のため Co2 センサー作り ー Arduino, BME280, MH-Z19編 | フレークの素 | Web制作・システム開発のCreativeFlakeブログ |](https://blog2.creativeflake.com/2017/04/22/%E3%82%AA%E3%83%95%E3%82%A3%E3%82%B9%E6%8F%9B%E6%B0%97%E3%81%AE%E3%81%9F%E3%82%81-co2-%E3%82%BB%E3%83%B3%E3%82%B5%E3%83%BC%E4%BD%9C%E3%82%8A-%E3%83%BC-arduino-bme280-mh-z19%E7%B7%A8/)

## Graph display

LCD also displays the graph of last 320 CO2 data.

## Demo

<blockquote class="twitter-tweet" data-lang="ja"><p lang="ja" dir="ltr">M5stackでCO2モニタ作ったぞい <a href="https://t.co/o72JZUw4XZ">pic.twitter.com/o72JZUw4XZ</a></p>&mdash; toms (@toms74209200) <a href="https://twitter.com/toms74209200/status/1129641057673666560?ref_src=twsrc%5Etfw">2019年5月18日</a></blockquote>
<script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>

## License

MIT License

## Author

[toms74209200](<https://github.com/toms74209200>)
