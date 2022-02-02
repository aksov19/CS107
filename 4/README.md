## ინსტრუქცია
- დააკლონირეთ რეპოზიტორია
- გახსენით ტერმინალი და გაუშვით `sh setup.sh` ან `./setup.sh`

### development

პრერეკვიზიტები. valgrind, zip, curl

```sh
sudo apt-get install valgrind #ubuntu
yay -S valgrind #arch

sudo apt-get install libcurl4-gnutls-dev #ubuntu
(32-ბიტიანი ვერსია: sudo apt-get install libcurl4-gnutls-dev:i386 #ubuntu)
sudo pacman -S libcurl-gnutls #arch
```

build

```sh
make
```

test

```sh
./assn-4-checker ./rss-news-search
./assn-4-checker ./rss-news-search -m
```
### შეფასება
./assn-4-checker ./rss-news-search -m

### ატვირთვა
google classroom-ზე.

#### version 1 ავტომატურად
გახსენით ტერმინალი და გაუშვით `./zip.sh`

#### version 2 manual
1. დაზიპეთ ფაილები `rss-news-search.cc`. **აუცილებელია იყოს `.zip` და არა rar**. დაზიპეთ **მხოლოდ** ეს ფაილები (სხვა ფაილებში ცვლილებები არ მიიღება) და არა დირექტორია
2. დაარქვით ზიპს თქვენი მეილის id


## კითხვები და დახმარება
თუ დავალებასთან დაკავშირებით კითხვა გქონდათ ან ტექნიკური დახმარება დაგჭირდათ:
1. ნახეთ შედით github.com-ზე დავალების გვერდზე და გახსენით [`faq.md`](./faq.md) ფაილი
2. თუ FAQ-ში არ არის, გადადით github-ზე დავალების `issues` განყოფილებაში. თუ ვინმეს უკვე აქვს დამატებული თქვენი კითხვა, დააკომენტარეთ რომ თქვენც გაქვთ, თუ საჭიროდ ჩათვლით დაურთეთ error message, სისტემის მონაცემები და ა.შ
3. თუ ვერცერთგან ვერ იპოვეთ, შექმენით ახალი `issue`

