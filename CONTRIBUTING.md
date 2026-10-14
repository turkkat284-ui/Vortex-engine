# CONTRIBUTING.md

Teşekkürler! Bu proje için katkıda bulunmak istemen harika — katkıların projenin gelişmesine yardımcı olur.

## Davranış Kuralları
Bu projede saygılı ve yapıcı bir iletişim beklenir. Kaba, aşağılayıcı veya dışlayıcı davranışlara izin verilmez. Daha ayrıntılı bir Kod Davranış Kuralları (Code of Conduct) eklemek isterseniz, bu dosyayı genişletebilirsiniz.

## Nasıl katkıda bulunulur
1. Depoyu fork'layın.
2. Yerel kopyanızı güncelleyin: `git clone <your-fork-url>` ve ana depoyu upstream olarak ekleyin.
3. Yeni bir branch oluşturun: `git checkout -b feature/isim` veya `fix/isim`.
4. Değişikliklerinizi küçük ve odaklı tutun. Her bir PR (Pull Request) tek bir amaç taşısın.
5. Değişiklikleri commit ederken anlamlı mesajlar kullanın: `feat: açıklama`, `fix: açıklama`, `docs: açıklama` vb.
6. Testler ekleyin/çalıştırın (varsa): `go test ./...`.
7. Değişiklikleri fork'a gönderin ve ana depoda yeni bir Pull Request açın. PR açıklamasında amacınızı, reproduksiyon adımlarını ve varsa test notlarını belirtin.

## Kod Stili ve Kalite
- Go kodu için `gofmt`/`goimports` kullanın.
- Linter kuralları varsa uyun (örneğin `golangci-lint`).
- Kritik veya düşük seviyeli C kodu değişikliklerinde dikkatli olun; değişikliklerin platform etkilerini ve güvenlik etkilerini açıklayın.

## Güvenlik ve Hassas Bilgi
Güvenlikle ilgili bir sorun fark ederseniz lütfen bunu kamuya açık issue olarak paylaşmayın; bunun yerine proje sahibinin SECURITY.md dosyasında belirtilen iletişim kanallarını kullanın.

## Issue ve Feature Talepleri
- Eğer bir hata bulduysanız, lütfen açık bir issue oluşturun ve hata/çökme adımlarını, ortam bilgilerini ekleyin.
- Yeni bir özellik öneriyorsanız, kullanım senaryosunu ve taslak bir çözümü kısa şekilde açıklayın.

## Lisans
Bu proje LICENSE dosyasında belirtilen lisans altında dağıtılmaktadır. Değişiklik gönderirken lisans uyumluluğunu gözetin.

Teşekkürler — katkılarınızı bekliyoruz!
