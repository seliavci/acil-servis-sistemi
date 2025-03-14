Acil Servis Sistemi Projesi

Proje Açıklaması
Bu proje, hastanede acil servis bölümündeki hasta kabul sistemini simüle eden bir yazılım uygulamasıdır. 
Amaç, gelen hastaların öncelik sırasına göre işlenmesi, bilgilerin HL7 formatında düzenlenmesi ve hastaların tedavi süreçlerine dair bazı temel işlemlerin yapılmasını sağlamaktır.


Projede aşağıdaki işlemler gerçekleştirilmiştir:
Hasta Kayıtları: Hastalar, TC kimlik numaraları, ad-soyad, doğum tarihi, cinsiyet, telefon numarası gibi temel bilgilerle sisteme kaydedilir.

Öncelik Sıralaması: Her hastaya acil durumuna göre bir öncelik derecesi atanır. Bu derecelere göre hastalar sıralanır.

HL7 Formatında Veri: Hastaların bilgileri HL7 formatına dönüştürülerek kaydedilir.

Reçete Üretimi: Her hastaya benzersiz bir reçete numarası atanır.


Özellikler

Hasta Kayıt Sistemi: Hastalar, sisteme temel bilgileri ile kaydedilir ve acil servis için başvuran her hastaya özel bir ID atanır.
Öncelik Sırası: Her hasta, öncelik derecesine göre sıralanır. Yüksek öncelikli hastalar önce kabul edilir.
HL7 Formatı: Hastaların bilgileri sağlık endüstrisinde yaygın olarak kullanılan HL7 formatında yazdırılır.
Reçete Numarası Üretme: Her hasta için benzersiz bir reçete numarası üretilir ve hasta bilgileriyle birlikte kaydedilir.


Kullanılan Teknolojiler

C Programlama Dili: Proje, C dilinde yazılmıştır.
Git ve GitHub: Proje sürüm kontrolü için Git kullanılmış ve GitHub üzerinde barındırılmaktadır.
HL7 Formatı: Hasta bilgileri, HL7 sağlık veri formatına dönüştürülür.


Gerekli Yazılımlar
C derleyicisi (örneğin, GCC) kurulu olmalıdır.
Git kurulumu yapılmış olmalıdır.


Proje Yapısı

acilServis.c: Ana uygulama dosyasını içerir. Hasta bilgileri burada işlenir ve sıralanır.
README.md: Projeye dair bilgiler, kurulum ve kullanım talimatları içerir.
Makefile (isteğe bağlı): Projenin derlenmesini ve çalıştırılmasını kolaylaştıran bir yapı dosyası.


HL7 Formatı

Hasta bilgileri, HL7 standardına uygun olarak aşağıdaki formatta yazdırılır:

MSH|^~\&|HastaneSistemi|AcilServis|HastaTakip|20250310||ADT^A01|123456|P|2.3
PID|||12345678901||Beyza Bilgit||2004-08-16|F|||05551234567||
PV1||Acil||||||||||||||HastaID1||
RXE|||RX-159393||

Bu formatta:

MSH: Mesaj başlık bilgileri.
PID: Hasta kimlik bilgileri.
PV1: Hasta kabul bilgileri.
RXE: Reçete numarası bilgileri.


Lisans

Bu proje, MIT Lisansı ile lisanslanmıştır. Detaylar için LICENSE dosyasına bakabilirsiniz.





















