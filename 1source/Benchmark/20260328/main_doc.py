import pathlib
from enum import StrEnum
from os import listdir
from os.path import isfile, join

import matplotlib
import matplotlib.pyplot as plt
import numpy as np

import csv

matplotlib.use("TkAgg")

PATH = pathlib.Path(__file__).parent


def moveavg(x, n):
    return np.convolve(x, np.ones(n) / n, mode="valid").tolist()


class Device(StrEnum):
    WIN = "win"
    LIN = "lin"
    LING = "ling"
    OLD = "OLD"


def device_name(dev: Device):
    match dev:
        case Device.WIN:
            return "Win10 Desktop"
        case Device.LIN:
            return "Mint laptop, integrated GPU"
        case Device.LING:
            return "Mint laptop, dedicated GPU"
        case Device.OLD:
            return "OLD Mint laptop, iGPU"


class Metric(StrEnum):
    RAM = "Využití operační paměti procesem [MiB]"
    CPU = "Celkové využití procesoru systémem [%]"
    DUR = "Doba trvání mezi dvěma měřeními [ms]"


def metric_str_short(met: Metric):
    match met:
        case Metric.RAM:
            return "RAM"
        case Metric.CPU:
            return "CPU"
        case Metric.DUR:
            return "DUR"


class Lib(StrEnum):
    DEAR = "DearImGui"
    DEAROPT = "DearImGuiOPT"  # Optimized to parse TOML only on text change
    EGUI = "egui"
    QT = "Qt"


def lib_str_short(lib: Lib):
    match lib:
        case Lib.DEAR:
            return "Dear"
        case Lib.DEAROPT:
            return "Dear"
        case Lib.EGUI:
            return "egui"
        case Lib.QT:
            return "Qt  "


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
        self.sample_n = []

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

        self.sample_n.append(len(self.sample_n) + 1)

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

    # for key, run in runs.items():
    #    print(f"{key.ljust(26)}{run.get_duration_str()}")

    libs = [Lib.DEAR, Lib.EGUI, Lib.QT]

    devices = [Device.WIN, Device.LING, Device.LIN]
    devices = [Device.LIN, Device.OLD]
    devices = [Device.LIN]

    device_linestyle = {
        Device.WIN: "-",
        Device.LIN: "-",
        Device.LING: "--",
        Device.OLD: "--"
    }

    do_moveavg = False
    n_subplots = 3

    metrics = [Metric.CPU]
    metrics = [Metric.RAM, Metric.CPU, Metric.DUR]

    for (img_idx, metric) in enumerate(metrics):

        print(img_idx)

        for benchtype in ["shon", "txoff"]:

            if metric == Metric.CPU and benchtype == "txoff":
                continue

            fig = plt.figure(figsize=(9, 3))
            axs = fig.subplots(1, n_subplots, sharey=True)
            ax_tops = [axs[idx].twiny() for idx in range(n_subplots)]

            # plt.suptitle(f"{str(metric)}", fontsize=14, fontweight="bold", y=0.95)

            for lib in libs:
                color = lib_color(lib)
                for dev in devices:
                    key = f"{str(lib)}_{str(dev)}_b3_{benchtype}"
                    arrx = runs[key].n_nodes[1:]
                    arry = runs[key].get_metric(metric)[1:]
                    arrs = runs[key].sample_n[1:]

                    p2start = next(i for i, v in enumerate(arrx) if v != 0)
                    p2end = next(i for i, v in enumerate(arrx) if v == 13230)

                    parts = [
                        (arrx[:p2start], arry[:p2start], arrs[:p2start]),
                        (arrx[p2start:p2end], arry[p2start:p2end], arrs[p2start:p2end]),
                        (arrx[p2end:], arry[p2end:], arrs[p2end:])
                    ]

                    for (idx, part) in enumerate(parts):
                        x_, y_, s_ = part

                        if do_moveavg and metric == Metric.CPU:
                            arry = moveavg(arry, 20)

                        axs[idx].plot(
                            y_,
                            color=color,
                            linestyle=device_linestyle[dev],
                            label=lib_str_long(lib),
                        )

                        step = 8
                        axs[idx].set_xticks(range(0, len(x_), step))
                        axs[idx].set_xticklabels([s_[i] for i in range(0, len(s_), step)],
                                                 rotation=40, ha="right")

                        ax_tops[idx].set_xlim(axs[idx].get_xlim())
                        ax_tops[idx].set_xticks(range(0, len(x_), step))
                        ax_tops[idx].set_xticklabels([max(x_[i], 1) for i in range(0, len(x_), step)],
                                                     rotation=40, ha="left")

                        if idx == 0:
                            axs[idx].set_xlabel("Číslo měření")
                            ax_tops[idx].set_xlabel("Počet vykreslených uzlů")
                            # ax_top.xaxis.set_label_coords(0.5, 1.08)

                            axs[idx].set_ylabel(str(metric))
                        # force y tick labels
                        # axs[idx].tick_params(labelleft=True)

                        axs[idx].margins(0, 0.05)

                        if idx == 2:
                            axs[idx].tick_params(labelright=True)
                            axs[idx].yaxis.set_tick_params(right=True, labelright=True)

            axs[0].legend(loc="upper left")

            fig.subplots_adjust(wspace=0.024)

            fig.savefig(f"figs2/nodes_{metric_str_short(metric)}_{benchtype}.pdf", bbox_inches="tight")
    # plt.tight_layout()
    # plt.show()


if __name__ == "__main__":
    main()
