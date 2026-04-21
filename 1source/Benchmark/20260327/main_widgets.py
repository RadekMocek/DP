import csv
import pathlib
from enum import StrEnum
from os import listdir
from os.path import isfile, join
from statistics import median

import matplotlib
import matplotlib.pyplot as plt

matplotlib.use("TkAgg")

PATH = pathlib.Path(__file__).parent


class Metric(StrEnum):
    DUR = "Doba potřebná k otevření okna [ms]"
    RAM = "Využití operační paměti procesem [MiB]"
    CPU = "Celkové využití procesoru systémem [%]"


class Lib(StrEnum):
    DEAR = "DearImGui"
    DEAROPT = "DearImGuiOPT"
    EGUI = "egui"
    QT = "Qt"


def lib_str_long(lib: Lib):
    match lib:
        case Lib.DEAR:
            return "Dear ImGui"
        case Lib.DEAROPT:
            return "Dear ImGui with TOML parse optimization"
        case Lib.EGUI:
            return "egui"
        case Lib.QT:
            return "Qt"


def lib_color(lib: Lib):
    match lib:
        case Lib.DEAR:
            return "blue"
        case Lib.DEAROPT:
            return "purple"
        case Lib.EGUI:
            return "orange"
        case Lib.QT:
            return "green"


class WBenchRun:
    def __init__(self, name):
        self.name = name
        self.n_batches = []
        self.iter = []
        self.duration = []
        self.mem_mib = []
        self.cpu_usage = []
        self.max_n_batches = 0
        self.second_max_n_batches = 0

    def append_csv_row(self, row: list[str]):
        curr_n_batches = int(row[0])
        self.n_batches.append(curr_n_batches)
        self.iter.append(int(int(row[1])))
        self.duration.append(int(row[2]))
        self.mem_mib.append(float(row[3]))
        self.cpu_usage.append(float(row[4]))

        self.second_max_n_batches = self.max_n_batches
        self.max_n_batches = max(curr_n_batches, self.max_n_batches)

    def get_total_duration_str(self):
        total_duration = sum(self.duration)
        return f"{total_duration / 1000} seconds"

    def get_metric(self, which: Metric):
        match which:
            case Metric.CPU:
                return self.cpu_usage
            case Metric.RAM:
                return self.mem_mib
            case Metric.DUR:
                return self.duration

    def get_medians(self, n_batches):
        indexes = [i for (i, x) in enumerate(self.n_batches) if x == n_batches]
        durs = [self.duration[i] for i in indexes]
        rams = [self.mem_mib[i] for i in indexes]
        if not durs and not rams:
            return None
        return median(durs), median(rams)


def init():
    path = PATH / "csv_widgets"
    filenames = [f for f in listdir(path) if isfile(join(path, f))]
    runs: dict[str, WBenchRun] = {}
    for filename in filenames:
        with open(path / filename, "r") as f:
            reader = csv.reader(f)
            run = WBenchRun(filename)
            is_first = True
            for row in reader:
                if is_first:
                    is_first = False
                    continue
                run.append_csv_row(row)
            runs[filename[14:-15]] = run
    return runs


def main_plot(runs):
    # for key, run in runs.items():
    #    print(f"{key.ljust(18)}{run.get_total_duration_str()}")

    devices = [
        # ("win", "-"),
        ("lin", "-"),
        # ("OLD", ":")
    ]

    libs = [Lib.DEAR, Lib.DEAROPT, Lib.EGUI, Lib.QT]
    libs = [Lib.DEAR, Lib.EGUI, Lib.QT]

    metrics = [Metric.RAM, Metric.CPU, Metric.DUR]
    metrics = [Metric.DUR, Metric.RAM]

    fig = plt.figure(figsize=(8, 3))
    axs = fig.subplots(1, 2)

    from_ = 19

    for (idx, metric) in enumerate(metrics):
        print(idx)
        for lib in libs:
            for dev_pair in devices:
                dev, linestyle = dev_pair
                key = f"{str(lib)}_{dev}"

                arry = runs[key].get_metric(metric)[from_:-1]

                axs[idx].set_title(f"{str(metric)}")

                axs[idx].plot(
                    arry,
                    color=f"{lib_color(lib)}",
                    linestyle=linestyle,
                    label=lib_str_long(lib),
                )

                if lib == Lib.DEAR:
                    arrx = runs[key].n_batches[from_:-1]
                    step = 20
                    axs[idx].set_xticks(range(0, len(arry), step))
                    axs[idx].set_xticklabels([arrx[i] for i in range(0, len(arrx), step)],
                                             rotation=50, ha="right")

        if idx == 0:
            axs[idx].set_xlabel("Počet „dávek“")
            axs[idx].xaxis.set_label_coords(1.07, -0.16)
            # axs[idx].annotate("Počet „dávek“:", xy=(0, 0), xytext=(-5, -7),ha="right", va="top",xycoords="axes fraction", textcoords="offset points")

    axs[1].legend(loc="upper left")
    fig.savefig(f"figs/widgets.pdf", bbox_inches="tight")
    # plt.show()


def main_table(runs):
    dev = "lin"
    dimg = runs[f"DearImGui_{dev}"]
    egui = runs[f"egui_{dev}"]
    qtxx = runs[f"Qt_{dev}"]
    max_n_batches = dimg.second_max_n_batches  # Real max is the last row of CSV (over 15 secs)

    result = "\\begin{table}\\rowcolors{2}{gray!10}{}\\begin{tabular}{|r||r|r|r||r|r|r|}\\hline\n"
    result += "&\\multicolumn{3}{c||}{Doba trvání [ms]}&\\multicolumn{3}{c|}{Využití RAM [MiB]}\\\\\n"
    result += "Pčt. widgetů & Dear & egui & Qt & Dear & egui & Qt\\\\\\hline\n"

    i = 1
    while True:
        result += "{:,} &".format(i * 172).replace(",", " ")

        dimg_vals = dimg.get_medians(i)
        egui_vals = egui.get_medians(i)
        qtxx_vals = qtxx.get_medians(i)

        for j in [0, 1]:

            result += f"{"{:,}".format(int(dimg_vals[j])).replace(",", " ") if dimg_vals else "—"} & "
            result += f"{"{:,}".format(int(egui_vals[j])).replace(",", " ") if egui_vals else "—"} & "
            result += f"{"{:,}".format(int(qtxx_vals[j])).replace(",", " ") if qtxx_vals else "—"}"
            if j == 0:
                result += " & "

        result += "\\\\\n"
        i *= 2
        if i > max_n_batches:
            break

    result += "\\end{tabular}\\end{table}"
    print(result)


if __name__ == "__main__":
    benchruns = init()
    main_plot(benchruns)
    # main_table(benchruns)
