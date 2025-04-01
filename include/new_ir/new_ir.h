#pragma once
// #define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace new_IR
{
    using namespace std;

    class porter_stemmer
    {
    public:
        porter_stemmer() : b(""), j(0), k(0), k0(0) {}
        ~porter_stemmer() {}

    private:
        bool cons(size_t i)
        {
            switch (b[i])
            {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return false;
            case 'y':
                return (i == k0 ? true : !cons(i - 1));
            }
            return true;
        }

        size_t m()
        {
            size_t n{};
            size_t i = k0;
            while (true)
            {
                if (i > j)
                    return n;
                if (!cons(i))
                    break;
                ++i;
            }
            ++i;
            while (true)
            {
                while (true)
                {
                    if (i > j)
                        return n;
                    if (cons(i))
                        break;
                    ++i;
                }
                ++i;
                ++n;
                while (true)
                {
                    if (i > j)
                        return n;
                    if (!cons(i))
                        break;
                    ++i;
                }
                ++i;
            }
        }

        bool vowelinstem()
        {
            for (size_t i = k0; i <= j; ++i)
                if (!cons(i))
                    return true;
            return false;
        }

        bool doublec(size_t j)
        {
            if (j < (k0 + 1))
                return false;
            if (b[j] != b[j - 1])
                return false;
            return cons(j);
        }

        bool cvc(size_t i)
        {
            if (i < (k0 + 2) || !cons(i) || cons(i - 1) || !cons(i - 2))
                return false;
            if (b[i] == 'w' || b[i] == 'x' || b[i] == 'y')
                return false;
            return true;
        }

        bool ends(string s)
        {
            size_t length = s.size();
            if (length > k - k0 + 1) return false;
            if (b.compare(k - length + 1, length, s) != 0) return false;
            j = k - length;
            return true;
        }

        void setto(string s)
        {
            size_t length = s.size();
            b = b.substr(0, j + 1) + s + b.substr(j + length + 1);
            k = j + length;
        }

        void r(string s)
        {
            if (m() > 0)
                setto(s);
        }

        void step1ab()
        {
            if (b[k] == 's')
            {
                if (ends("sses"))
                    k -= 2;
                else if (ends("ies"))
                    setto("i");
                else if (b[k - 1] != 's')
                    --k;
            }
            if (ends("eed"))
            {
                if (m() > 0)
                    --k;
            }
            else if ((ends("ed") || ends("ing")) && vowelinstem())
            {
                k = j;
                if (ends("at"))
                    setto("ate");
                else if (ends("bl"))
                    setto("ble");
                else if (ends("iz"))
                    setto("ize");
                else if (doublec(k))
                {
                    k--;
                    char ch = b[k];
                    if (ch == 'l' || ch == 's' || ch == 'z')
                        k++;
                }
                else if (m() == 1 && cvc(k))
                    setto("e");
            }
        }

        void step1c()
        {
            if (ends("y") && vowelinstem())
                b = b.substr(0, k) + "i" + b.substr(k + 1, b.size() - 1);
        }

        void step2()
        {
            switch (b[k - 1])
            {
            case 'a':
                if (ends("ational"))
                    r("ate");
                else if (ends("tional"))
                    r("tion");
                break;
            case 'c':
                if (ends("enci"))
                    r("ence");
                else if (ends("anci"))
                    r("ance");
                break;
            case 'e':
                if (ends("izer"))
                    r("ize");
                break;
            case 'l':
                if (ends("bli"))
                    r("ble");
                else if (ends("alli"))
                    r("al");
                else if (ends("entli"))
                    r("ent");
                else if (ends("eli"))
                    r("e");
                else if (ends("ousli"))
                    r("ous");
                break;
            case 'o':
                if (ends("ization"))
                    r("ize");
                else if (ends("ation"))
                    r("ate");
                else if (ends("ator"))
                    r("ate");
                break;
            case 's':
                if (ends("alism"))
                    r("al");
                else if (ends("iveness"))
                    r("ive");
                else if (ends("fulness"))
                    r("ful");
                else if (ends("ousness"))
                    r("ous");
                break;
            case 't':
                if (ends("aliti"))
                    r("al");
                else if (ends("iviti"))
                    r("ive");
                else if (ends("biliti"))
                    r("ble");
                break;
            case 'g':
                if (ends("logi"))
                    r("log");
            }
        }

        void step3()
        {
            switch (b[k])
            {
            case 'e':
                if (ends("icate"))
                    r("ic");
                else if (ends("ative"))
                    r("");
                else if (ends("alize"))
                    r("al");
                break;
            case 'i':
                if (ends("iciti"))
                    r("ic");
                break;
            case 'l':
                if (ends("ical"))
                    r("ic");
                else if (ends("ful"))
                    r("");
                break;
            case 's':
                if (ends("ness"))
                    r("");
            }
        }

        void step4()
        {
            switch (b[k - 1])
            {
            case 'a':
                if (ends("al"))
                    ;
                else
                    return;
                break;
            case 'c':
                if (ends("ance"))
                    ;
                else if (ends("ence"))
                    ;
                else
                    return;
                break;
            case 'e':
                if (ends("er"))
                    ;
                else
                    return;
                break;
            case 'i':
                if (ends("ic"))
                    ;
                else
                    return;
                break;
            case 'l':
                if (ends("able"))
                    ;
                else if (ends("ible"))
                    ;
                else
                    return;
                break;
            case 'n':
                if (ends("ant"))
                    ;
                else if (ends("ement"))
                    ;
                else if (ends("ment"))
                    ;
                else if (ends("ent"))
                    ;
                else
                    return;
                break;
            case 'o':
                if (ends("ion") && (b[j] == 's' || b[j] == 't'))
                    ;
                else if (ends("ou"))
                    ;
                else
                    return;
                break;
            case 's':
                if (ends("ism"))
                    ;
                else
                    return;
                break;
            case 't':
                if (ends("ate"))
                    ;
                else if (ends("iti"))
                    ;
                else
                    return;
                break;
            case 'u':
                if (ends("ous"))
                    ;
                else
                    return;
                break;
            case 'v':
                if (ends("ive"))
                    ;
                else
                    return;
                break;
            case 'z':
                if (ends("ize"))
                    ;
                else
                    return;
                break;
            }
        }

        void step5()
        {
            j = k;
            if (b[k] == 'e')
            {
                size_t a = m();
                if (a > 1 || (a == 1 && !cvc(k - 1)))
                    --k;
            }
            if (b[k] == 'l' && doublec(k) && m() > 1)
                --k;
        }

    public:
        const string stem(const string& p, size_t i = 0, size_t j = 0)
        {
            b = p;
            if (j == 0)
                j = p.length() - 1;
            k = j;
            k0 = i;
            if (k <= k0 + 1)
                return b;

            step1ab();
            step1c();
            step2();
            step3();
            step4();
            step5();
            return b.substr(k0, k + 1);
        }

        const string operator()(const string& p, size_t i = 0, size_t j = 0)
        {
            return stem(p, i, j);
        }
    private:
        string b;
        size_t k0 = 0, k, j;
    };

    class new_ir
    {
    private:
        void split_words(string doc, vector<string>& words)
        {
            char* s = new char[doc.length() + 1] {};
            strcpy(s, doc.c_str());
            char delimiter[] = " ,.?!()\"\t\n";
            char* token = strtok(s, delimiter);

            while (token != nullptr)
            {
                string term(token);

                bool is_all_upper = all_of(term.begin(), term.end(), [](unsigned char ch) {return isupper(ch); });
                transform(term.begin(), term.end(), term.begin(), ::tolower);
                if (stop_words.find(term) == stop_words.end() || is_all_upper)
                    words.emplace_back(stemmer.stem(term));

                token = strtok(nullptr, delimiter);
            }

            delete[] s;
        }
    public:
        new_ir(const std::string& doc) : stemmer()
        {
            vector<string> words;
            split_words(doc, words);

            unordered_map<string, size_t> words_cnt;
            for (auto& s : words)
                ++words_cnt[s];
            /*
            for (auto& s : words)
                words_map[s] = ((double)words_cnt[s] / words.size()) * log((double)words.size() / words_cnt[s]);
            // td - idf
            */
            for (auto& s : words)
                words_map[s] = ((double)words_cnt[s] / words_cnt.size()) * log((double)words_cnt.size() / words_cnt[s]) * (1 + 0.3 * log(s.length()));
        }

        double query(const string& word)
        {
            string term = stemmer.stem(word);
            if (words_map.find(term) != words_map.end())
                return words_map[term];
            return 0.0;
        }

        const unordered_map<string, double>& get_words_map()
        {
            return words_map;
        }

    private:
        porter_stemmer stemmer;
        unordered_map<string, double> words_map;
        const unordered_set<string> stop_words =
        {
            "a", "an", "the", "and", "or", "but", "if", "of", "at", "by",
            "for", "with", "about", "between", "during", "as"

            "this", "that", "these", "those", "be", "is", "are", "was", "were",
            "have", "has", "had", "do", "does", "did",

            "in", "on", "to", "from", "up", "down", "over", "under",
            "after", "before", "into", "onto", "upon",

            "while", "when", "where", "how", "why", "because", "since",
            "although", "however", "therefore"
        };
    };
}
