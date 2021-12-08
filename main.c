#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct Kelimeler
{
    int tutucu;
    struct Kelimeler *next;
    char *str;
} kelimeler;

kelimeler *kelime_yap (char *kelime)
{
    kelimeler *yeniKelime =(kelimeler*) malloc (sizeof (kelimeler));

    if (NULL != yeniKelime)
    {
        yeniKelime->str = (char *) malloc ((strlen (kelime)) + 1);
        strcpy (yeniKelime->str, kelime);
        yeniKelime->str[strlen (kelime)] = '\0';

        printf (" Olusan kelime: %s ", yeniKelime->str);

        yeniKelime->tutucu = 1;
        yeniKelime->next = NULL;
    }
    return yeniKelime;
}

kelimeler *kelime_ekle (kelimeler **kelimeListesi, char *kelime)
{

    if (!*kelimeListesi)
    {
        printf ("LISTE\n");
        return *kelimeListesi = kelime_yap (kelime);
    }

    kelimeler *temp = *kelimeListesi;
    while (temp->next != NULL)
    {
        if (strcmp (temp->str, kelime) == 0)
        {
            temp->tutucu = temp->tutucu + 1;
            return *kelimeListesi;
        }
        else
            temp = temp->next;
    }

    kelimeler *yeniKelime = kelime_yap (kelime);
    if (NULL != yeniKelime)
    {
        temp->next = yeniKelime;
        printf (" Yeni Kelime: %s\n ", yeniKelime->str);
    }
    return yeniKelime;
}

int main (int argc, char *argv[])
{
    int a=1;
    kelimeler *kelime1;
    char *karakter = " ,:;\t\n";
    kelime1 = NULL;

    FILE *dosya = fopen ("Deneme.txt", "r");
    if (dosya == 0)
    {
        printf ("dosya acilamadi\n");
        return 1;
    }
    else
    {
        printf ("dosya acildi \n");
    }

    char kelimetutucu[100];
    int ch = 0, kelime = 1, k = 0;

    while ((ch = fgetc (dosya)) != EOF)
    {
        if (strchr (karakter, ch))
        {
            if (kelime == 1)
            {
                kelime = 0;
                kelimetutucu[k] = '\0';

                printf ("\nkelime_ekle (kelime, %s)\n", kelimetutucu);

                if (kelime_ekle (&kelime1, kelimetutucu))
                {
                    printf (" eklenen: %s\n", kelimetutucu);
                }
                else
                {
                    fprintf (stderr, "error: kelime_ekle basarisiz.\n");
                }

                k = 0;
            }
        }
        else
        {
            kelime = 1;
            kelimetutucu[k++] = tolower (ch);
        }
    }
    if (kelime == 1)
    {
        kelimetutucu[k] = '\0';
        printf ("\nkelime_ekle (kelime, %s) (önceki)\n", kelimetutucu);
        if (kelime_ekle (&kelime1, kelimetutucu))
        {
            printf (" eklenen: %s\n", kelime1->str);
        }
        else
        {
            fprintf (stderr, "hata: kelime_ekle basarisiz.\n");
        }
    }

    kelimeler *aktarilan;
    printf ("yazdirilan liste\n");

    FILE *dosya1= fopen ("Cikti.txt", "w+");
    if (dosya1 == 0)
    {
        printf ("çıktı dosyasi acilamadi \n");
        return 1;
    }
    else
    {
        printf ("çıktı dosyasi acildi \n");
    }

    aktarilan = kelime1;

    while (aktarilan != NULL)
    {
        fprintf (dosya1,"%d-) %s :%d \n", a, aktarilan->str, aktarilan->tutucu);
        printf ("%d-) %s :%d \n", a, aktarilan->str, aktarilan->tutucu);
        aktarilan = aktarilan->next;
        a++;
    }

    putchar ('\n');
    return 0;
}

