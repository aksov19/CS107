## ინსტრუქცია
- დააკლონირეთ რეპოზიტორია
- გახსენით ტერმინალი და გაუშვით `sh setup.sh` ან `./setup.sh`

### development

პრერეკვიზიტები. valgrind, zip 

```sh
sudo apt-get install valgrind #ubuntu
yay -S valgrind #arch
```

build

```sh
make
```

test

```sh
./vector-test
./hashset-test
```

### შეფასება
ტესტერების წარმატებული output არის sample-output-vector.txt და sample-output.hashset.txt.

იმისთვის, რომ შეამოწმოთ რა ხაზებზე განსხვავდება თქვენი და სწორი output, შეგიძლიათ გამოიყენოთ პროგრამა diff (ამ ბრძანებების მეშვეობით)
```sh
./vector-test | diff sample-output-vector.txt - 
./hashset-test | diff sample-output-hashset.txt -
```


### ატვირთვა
google classroom-ზე.

#### version 1 ავტომატურად
გახსენით ტერმინალი და გაუშვით `./zip.sh`

#### version 2 manual
1. დაზიპეთ ფაილები `vector.c vector.h hashset.c hashset.h`. **აუცილებელია იყოს `.zip` და არა rar**. დაზიპეთ **მხოლოდ** ეს ფაილები (სხვა ფაილებში ცვლილებები არ მიიღება) და არა დირექტორია
2. დაარქვით ზიპს თქვენი მეილის id


## კითხვები და დახმარება
თუ დავალებასთან დაკავშირებით კითხვა გქონდათ ან ტექნიკური დახმარება დაგჭირდათ:
1. ნახეთ შედით github.com-ზე დავალების გვერდზე და გახსენით [`faq.md`](./faq.md) ფაილი
2. თუ FAQ-ში არ არის, გადადით github-ზე დავალების `issues` განყოფილებაში. თუ ვინმეს უკვე აქვს დამატებული თქვენი კითხვა, დააკომენტარეთ რომ თქვენც გაქვთ, თუ საჭიროდ ჩათვლით დაურთეთ error message, სისტემის მონაცემები და ა.შ
3. თუ ვერცერთგან ვერ იპოვეთ, შექმენით ახალი `issue`

