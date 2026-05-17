#include <nstl/string.h>

namespace nstl::algo {
    template <typename T>
    static T min(T arg) {
        return arg;
    }

    template <typename T, typename ...Args>
    T min(T arg, Args... args) {
        T rec = min(args...);
        return arg < rec ? arg : rec;
    }

    template <typename T>
    static T max(T arg) {
        return arg;
    }

    template <typename T, typename ...Args>
    T max(T arg, Args... args) {
        T rec = max(args...);
        return arg > rec ? arg : rec;
    }


void zalgsuff(const nstl::string& nstr, size_t*& suffs) {
    if (nstr.size() == 0) return;

    suffs = new size_t[nstr.size()];
    size_t l, r;
    l = r = nstr.size() - 1;

    suffs[nstr.size() - 1] = nstr.size();

    if (r == 0) return;
    --r;

    while (l > 0) {
        // Find largest substring [..., r] that is a suffix of nstr
        for (; l > 0 && nstr[l - 1] == nstr[nstr.size() - 1 - r + l - 1];) {
            --l;
        }

        suffs[r] = r + 1 - l;

        // Fill in the suffs entries of those in the Z-box
        for (size_t i = r; i-- > l;) {
            size_t twin_idx = nstr.size() - 1 - r + i;

            // If its suffs entry has not yet been defined or it gets out of Z-box, start new Z-box from here
            if (l > 0 && (twin_idx == i || i < l + suffs[twin_idx] - 1)) {
                r = i;
                break;
            }

            suffs[i] = l > 0 ? suffs[twin_idx] : min(suffs[twin_idx], i + 1);
        }

        if (r < l) {
            --l;
        }

        r = l - 1;
    }
}

void zborders(const nstl::string& nstr, size_t*& borders) {
    if (nstr.size() == 0) return;

    size_t* suffs;
    borders = new size_t[nstr.size()];

    zalgsuff(nstr, suffs);

    for (size_t i = 0; i < nstr.size(); ++i) {
        std::cout << suffs[i] << " ";
    }
    std::cout << std::endl;

    borders[nstr.size() - 1] = 1;
    size_t edge = nstr.size() - 1;
    for (size_t i = nstr.size() - 1; i-- > 0;) {
        if (edge <= i + 1 - suffs[i]) {
            if (edge == i + 1) {
                --edge;
                borders[i] = 0;
            }
            continue;
        }

        size_t initial_fuel = suffs[i] + edge - i - 1;
        for (size_t fuel = initial_fuel; fuel-- > 0;) {
            borders[edge - initial_fuel + fuel] = initial_fuel - fuel;
        }

        edge = i + 1 - suffs[i];
    }
}

void shifts(const nstl::string& nstr, size_t*& shifts) {
    if (nstr.size() == 0) return;

    size_t* borders;
    shifts = new size_t[nstr.size()];
    zborders(nstr, borders);

    for (size_t i = 0; i < nstr.size(); ++i) {
        std::cout << borders[i] << " ";
    }
    std::cout << std::endl;

    for (size_t i = nstr.size(); i-- > 0;) {
        shifts[i] = i + 1;

        if (shifts[nstr.size() - 1 - borders[i]] < nstr.size() - borders[i]) {
            continue;
        }

        if (i > 0 && nstr[i - 1] == nstr[nstr.size() - 1 - borders[i]]) {
            continue;
        }

        if (borders[i] == 0) {
            shifts[nstr.size() - 1] = nstr.size() - 1 - i;
            continue;
        }

        shifts[nstr.size() - 1 - borders[i]] = nstr.size() - 1 - borders[i] - (i - 1);
    }
};
}