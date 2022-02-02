## ინსტრუქცია
- დააკლონირეთ რეპოზიტორია

### development

პრერეკვიზიტები. kawa, zip 

test

```sh
kawa

(load "where-am-i.scm")
(test-intersection-points) 
(test-distance-product)
(test-rate-points)
(test-sort-points)
(test-clumped-points)
(test-average-point)
(test-best-estimate)
(test-where-am-i))
```

test-all

```sh
kawa

(load "where-am-i.scm")
(test-all)
```
### შეფასება
test-all

### ატვირთვა
google classroom-ზე.

#### version 1 ავტომატურად
გახსენით ტერმინალი და გაუშვით `./zip.sh`

#### version 2 manual
1. დაზიპეთ ფაილები `where-am-i.scm`. **აუცილებელია იყოს `.zip` და არა rar**. დაზიპეთ **მხოლოდ** ეს ფაილები (სხვა ფაილებში ცვლილებები არ მიიღება) და არა დირექტორია
2. დაარქვით ზიპს თქვენი მეილის id


## კითხვები და დახმარება
თუ დავალებასთან დაკავშირებით კითხვა გქონდათ ან ტექნიკური დახმარება დაგჭირდათ:
1. ნახეთ შედით github.com-ზე დავალების გვერდზე და გახსენით [`faq.md`](./faq.md) ფაილი
2. თუ FAQ-ში არ არის, გადადით github-ზე დავალების `issues` განყოფილებაში. თუ ვინმეს უკვე აქვს დამატებული თქვენი კითხვა, დააკომენტარეთ რომ თქვენც გაქვთ, თუ საჭიროდ ჩათვლით დაურთეთ error message, სისტემის მონაცემები და ა.შ
3. თუ ვერცერთგან ვერ იპოვეთ, შექმენით ახალი `issue`

