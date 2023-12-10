<h1 align="center">Master Thesis</h1>
<p align="center">
   Containerization in High-Performance Computing (HPC)
</p>
<br>

This repository hosts documentation, guides and work related to my master thesis at TUM under 
[Prof. Carsten Trinitis](https://www.ce.cit.tum.de/en/caps/staff/carsten-trinitis/) within the 
Chair of Computer Architecture and Parallel Systems, also co-supervised by 
[Dr. Hubertus Franke](https://cims.nyu.edu/~frankeh/) an adjunct professor at NYU .


<details open>
<summary> <b>ROADMAP</b> </summary>
<p>

- To-do
    - [ ] Look Into
        + [ ] Containers in HPC
        + [ ] Singularity
- Academia
    - [X] Email Carsten
    - [ ] Update Franke

</p>
</details>


<details closed>
<summary>
    <b>PAPERS & <a href="https://github.com/duclos-cavalcanti/msc-thesis/wiki/Documentation">NOTES</a></b> 
</summary>
<p>
<table>

<tr> <th>Title</th> <th>Date</th> </tr>

<tr>
    <td>
    <a href="https://onlinelibrary.wiley.com/doi/full/10.1002/cpe.7976">
    HPC applications on public clouds with HPC@Cloud toolkit
    </a> ( 
    <a href="https://sol.sbc.org.br/index.php/wscad/article/view/21941">
    Older Version
    </a> )
    </td>
    <td> <em>2023</em> </td> 
</tr>

<tr>
    <td>
    <a href="https://link.springer.com/article/10.1007/s11227-022-04848-y">
    Containers in HPC: a survey
    </a>
    </td> <td> <em>2022</em> </td>
</tr>

<tr>
    <td>
    <a href="https://dl.acm.org/doi/abs/10.1145/3447545.3451183">
    10 Years Later: Cloud Computing is Closing the Performance Gap
    </a>
    </td>
    <td> <em>2021</em> </td> 
</tr>

<tr>
    <td>
    <a href="https://journals.plos.org/plosone/article?id=10.1371/journal.pone.0177459">
    Singularity: Scientific containers for mobility of compute
    </a>
    </td>
    <td> <em>2017</em> </td> 
</tr>

<tr>
    <td>
    <a href="https://ieeexplore.ieee.org/document/8241093">
    A Tale of Two Systems: Using Containers to Deploy HPC Applications on Supercomputers and Clouds
    </a>
    </td>
    <td> <em>2017</em> </td> 
</tr>

<tr>
    <td>
    <a href="https://ieeexplore.ieee.org/document/7933304">
    Containers for Portable, Productive, and Performant Scientific Computing
    </a>
    </td>
    <td> <em>2017</em> </td> 
</tr>

</table> 
</p>
</details>


## Introduction

__Abstract:__ _Not defined yet._

- [Kickoff](https://docs.google.com/presentation/d/1RYzUNyqYfQWafwH4Xe0ic6VNJ8tZ2MTnJNR1RxLthOw/edit?usp=sharing)
- [Presentation](https://docs.google.com/presentation/d/1RRkn1ZtRFq8zkE4Z4c-2xnu5dK6mD9ZrlY_gs_kPFrs/edit?usp=sharing)

Check out the [_wiki_](https://github.com/duclos-cavalcanti/msc-thesis/wiki) for more!

## 1. Setup

1. Clone the repo
   ```bash
   git clone https://github.com/duclos-cavalcanti/msc-thesis.git
   ```

2. Install dependencies _([singularity](https://docs.sylabs.io/guides/4.0/user-guide/quick_start.html#quick-installation-steps))_
   ```bash
    # based on debian/ubuntu systems
    sudo apt install build-essential

    # open-mpi
    sudo apt install openmpi-bin openmpi-doc libopenmpi-dev

    # singularity, squashfs-tools-ng is necessary for OCI-mode!
    sudo apt-get install -y \
       autoconf \
       automake \
       cryptsetup \
       git \
       libfuse-dev \
       libglib2.0-dev \
       libseccomp-dev \
       libtool \
       pkg-config \
       runc \
       squashfs-tools \
       squashfs-tools-ng \
       uidmap \
       wget \
       zlib1g-dev
    ```

3. Following _([singularity](https://docs.sylabs.io/guides/4.0/user-guide/quick_start.html#quick-installation-steps))_
    1. Install [Golang](https://go.dev/dl/)
    ```bash 
    export VERSION=1.21.0 OS=linux ARCH=amd64 && \
        wget https://dl.google.com/go/go$VERSION.$OS-$ARCH.tar.gz && \
        sudo tar -C /usr/local -xzvf go$VERSION.$OS-$ARCH.tar.gz && \
        rm go$VERSION.$OS-$ARCH.tar.gz

    echo 'export PATH=/usr/local/go/bin:$PATH' >> ~/.bashrc && \
        source ~/.bashrc
    ```
    2. Download [SingularityCE](https://docs.sylabs.io/guides/4.0/user-guide/quick_start.html#download)
    ```bash 
    export VERSION=4.0.0 && \
        wget https://github.com/sylabs/singularity/releases/download/v${VERSION}/singularity-ce-${VERSION}.tar.gz && \
        tar -xzf singularity-ce-${VERSION}.tar.gz && \
        cd singularity-ce-${VERSION} 
    ```
    3. Compile [SingularityCE](https://docs.sylabs.io/guides/4.0/user-guide/quick_start.html#compile)
    ```bash 
    $ ./mconfig && \
        make -C builddir && \
        sudo make -C builddir install
    ```

## 2. Usage

1. Build
    ```bash 
    make build
    ```

2. Run
    ```bash 
    make run
    ```

## 3. License
This project is released under the BSD 3-Clause license. See [LICENSE](LICENSE).

## 4. Resources 
- [OCI](https://opencontainers.org/)
- [singularity](https://sylabs.io/docs/)
- [singularity-4.0-user-guide](https://docs.sylabs.io/guides/4.0/user-guide/)
- [singularity-4.0-installation](https://docs.sylabs.io/guides/4.0/user-guide/quick_start.html#quick-installation-steps)

---
<p align="center">
<a href="https://github.com/duclos-cavalcanti/templates/LICENSE">
  <img src="https://img.shields.io/badge/license-BSD3-yellow.svg" />
</a>
<a>
  <img src="https://img.shields.io/github/languages/code-size/duclos-cavalcanti/msc-thesis.svg" />
</a>
<a>
  <img src="https://img.shields.io/github/commit-activity/m/duclos-cavalcanti/msc-thesis.svg" />
</a>
</p>
