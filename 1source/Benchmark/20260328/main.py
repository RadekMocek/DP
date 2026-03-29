import csv
import pathlib
from enum import StrEnum
from os import listdir
from os.path import isfile, join

import matplotlib.pyplot as plt

PATH = pathlib.Path(__file__).parent


class Metric(StrEnum):
    RAM = "RAM Resident Set Size [MiB]"
    CPU = "System CPU [%]"
    DUR = "Time interval between two measures [ms]"


class Lib(StrEnum):
    DEAR = "DearImGui"
    DEAROPT = "DearImGuiOPT"
    EGUI = "egui"
    QT = "Qt"


class Mod(StrEnum):
    SHON = "shon"
    TXOFF = "txoff"


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


def mod_desc(mod: Mod):
    match mod:
        case Mod.SHON:
            return "Text editor with syntax highlight visible"
        case Mod.TXOFF:
            return "Text editor hidden"


class BenchRun:
    def __init__(self, name):
        self.name = name
        self.timestamp = []
        self.fps = []
        self.n_nodes = []
        self.mem_mib = []
        self.cpu_usage = []

        self.time_diff = []

    def append_csv_row(self, row: list[str]):
        current_timestamp = int(row[0])
        self.timestamp.append(current_timestamp)
        self.fps.append(int(float(row[1])))
        self.n_nodes.append(int(row[2]))
        self.mem_mib.append(float(row[3]))
        self.cpu_usage.append(float(row[4]))

        if len(self.timestamp) == 1:
            self.time_diff.append(current_timestamp)
        else:
            self.time_diff.append(current_timestamp - self.timestamp[-2])

    def get_duration_str(self):
        duration = self.timestamp[-1] - self.timestamp[0]
        return f"{duration / 1000} seconds"

    def get_metric(self, which: Metric):
        match which:
            case Metric.CPU:
                return self.cpu_usage
            case Metric.RAM:
                return self.mem_mib
            case Metric.DUR:
                return self.time_diff


METRICS = [Metric.RAM, Metric.CPU, Metric.DUR]


def main():
    path = PATH / "csv"
    filenames = [f for f in listdir(path) if isfile(join(path, f))]
    runs: dict[str, BenchRun] = {}
    for filename in filenames:
        with open(path / filename, "r") as f:
            reader = csv.reader(f)
            run = BenchRun(filename)
            is_first = True
            for row in reader:
                if is_first:
                    is_first = False
                    continue
                run.append_csv_row(row)
            runs[filename[8:-15]] = run

    for key, run in runs.items():
        print(f"{key.ljust(26)}{run.get_duration_str()}")

    device = "lin"

    # libs = [Lib.DEAR, Lib.DEAROPT, Lib.EGUI, Lib.QT]
    libs = [Lib.DEAR, Lib.EGUI, Lib.QT]

    mods = [Mod.SHON, Mod.TXOFF]

    for metric in METRICS:
        fig, axs = plt.subplots(len(mods), 1)
        plt.suptitle(f"{str(metric)}", fontsize=16, fontweight="bold")
        for lib in libs:
            key = f"{str(lib)}_{device}_b3_"
            for (i, mod) in enumerate(mods):
                axs[i].set_title(mod_desc(mod))

                arr = runs[key + str(mod)].get_metric(metric)[1:]
                min_ = int(min(arr))
                max_ = int(max(arr))
                axs[i].plot(range(len(arr)), arr, color=f"{lib_color(lib)}",
                            label=f"{str(lib).ljust(9)} [{min_}–{max_}]")

                x_axis = runs[key + str(mod)].n_nodes[1:]
                step = 8
                axs[i].set_xticks(range(0, len(x_axis), step))
                axs[i].set_xticklabels([max(x_axis[i], 1) for i in range(0, len(x_axis), step)],
                                       rotation=40, ha="right")

                axs[i].axvline(x=64, color="black", lw=0.4)
                axs[i].axvline(x=128, color="black", lw=0.4)
                axs[i].legend(prop={"family": "monospace"})
        # fig.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
