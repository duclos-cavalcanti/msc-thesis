<h1 align="center">Master Thesis</h1>
<p align="center">
    Virtual Real-Time Scheduling
</p>
<br>

This repository hosts documentation, guides and work related to my master thesis at TUM under 
[Prof. Carsten Trinitis](https://www.ce.cit.tum.de/en/caps/staff/carsten-trinitis/) within the 
Chair of Computer Architecture and Parallel Systems, also co-supervised by 
[Dr. Hubertus Franke](https://cims.nyu.edu/~frankeh/) an adjunct professor at NYU .


<details closed>
<summary> <b>ROADMAP</b> </summary>
<p>

- To-do
    - [ ] Look Into
        + [ ] Virtual Real-Time Scheduling
        + [ ] Real-Time Linux
        + [ ] Linux Kernel
        + [ ] `cyclic-test`
        + [ ] `rtsl`
- Academia
    - [X] Email Carsten
    - [ ] Update Franke

</p>
</details>

<details closed>
<summary> <b>PAPERS</b> </summary>
<p>
<table>
<tr> <th>VM Scheduling</th> <th>Date</th> </tr>
<tr>
    <td> 
    *
    <a href="https://www.sciencedirect.com/science/article/pii/S016412121830270X">
    Hierarchical scheduling of real-time tasks over Linux-based virtual machines
    </a>
    </td>
    <td> <em>2019</em> </td> 
</tr>
<tr>
    <td>
    <a href="https://dl.acm.org/doi/abs/10.1145/3373400.3373405">
    Container-based real-time scheduling in the linux kernel
    </a>
    </td> <td> <em>2019</em> </td>
</tr>
<tr>
    <td>
    <a href="https://drops.dagstuhl.de/storage/01oasics/oasics-vol080-fog-iot2020/OASIcs.Fog-IoT.2020.7/OASIcs.Fog-IoT.2020.7.pdf">
    Real-Time Containers: A Survey
    </a>
    </td>
    <td> <em>2020</em> </td> 
</tr>
<tr>
    <td> 
    <a href="https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=6059185&tag=1">
    Towards Real-Time Scheduling of Virtual Machines Without Kernel Modifications
    </a>
    </td>
    <td> <em>2011</em> </td> 
</tr>
<tr> <th>Linux and RT-Scheduling</th> <th>Date</th>
</tr>
<tr>
    <td>
    <a href="http://code.ua.pt/attachments/download/1649/_Current_Approaches_and_Future_Opportunities.pdf">
    Linux and real-time: Current approaches and future opportunities
    </a>
    </td> <td> <em>2006</em> </td>
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

2. Installation
    * Dependencies: ([qemu](https://www.qemu.org/), [kvm](https://www.linux-kvm.org/page/Main_Page), [libvirt](https://libvirt.org/), [packer](https://developer.hashicorp.com/packer/tutorials/docker-get-started/get-started-install-cli))_
    * Based on `debian`/`ubuntu` systems
   ```bash
    # qemu, kvm and network utils
    sudo apt install qemu-kvm qemu-utils
    sudo apt install libvirt-dev libvirt-daemon-system libvirt-clients
    sudo apt install bridge-utils
    ```

    ```bash
    # packer
    curl -fsSL https://apt.releases.hashicorp.com/gpg | sudo apt-key add -
    sudo apt-add-repository "deb [arch=amd64] https://apt.releases.hashicorp.com $(lsb_release -cs) main"
    sudo apt-get update && sudo apt-get install packer
    ```

3. Add user to `libvirt` group
   ```bash
    sudo usermod -aG libvirt $(whoami)
   ```

4. Verify that `libvirt` is installed and running:
    ```
    virsh -c qemu:///system list
    ```

5. Verify `kvm`  is properly setup 
    ```bash 
    lsmod | grep kvm
    ```

6. Start the `libvirtd` service 
    ```bash 
    sudo systemctl enable --now libvirtd
    ```

## 2. Usage

1. Run
    ```bash 
    make run
    ```

## 3. License
This project is released under the BSD 3-Clause license. See [LICENSE](LICENSE).

---
<p align="center">
<a href="https://github.com/duclos-cavalcanti/templates/LICENSE">
  <img src="https://img.shields.io/badge/license-BSD3-yellow.svg" />
</a>
<a>
  <img src="https://img.shields.io/github/languages/code-size/duclos-cavalcanti/dotfiles.svg" />
</a>
<a>
  <img src="https://img.shields.io/github/commit-activity/m/duclos-cavalcanti/dotfiles.svg" />
</a>
</p>
