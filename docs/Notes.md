# Slide 0 - Background /  Slide 1 - Motivation: Unikernels
Virtualization:

- 1960's, IBM developed virtual machine technology for its mainframe computers. 
    - Addressed: 
	    - Mainframes were too expensive 
	    - Shortcomings in resource usage/allocation
	    - Difficulties w/ legacy software that was not designed for efficient share multi-tenancy.
        - Lack of isolation (sensitive data)
- Popularization in the 2000s due to the rise of x86-based servers, the need for robust and reproducible software testing and development, and the rise of cloud computing as an IT paradigm.
- Virtualization Provides(d): 
    - Better Resource Utilization/Efficiency
	- Scalability (Management Complexity)
	- Flexibility (Different OSes, Restructure) 
	- Isolation (Security)
- Virtualization/VM’s are building blocks of Cloud Computing as they enable better scalability and resource utilization of physical servers. 

Hypervisors: 
- Software/Hardware Layer that enables virtualization. 
- Types:

- 1 or Bare-Metal: Run directly on physical hardware of
the host system w/o the need of an OS. Have direct control 
over hardware resources. 
	- High Performance, Efficient (no intermediary)
	- Enhanced Security (no Host OS)
	- Less user-friendly 

- 2 or Hosted: 
    - Run on top of an OS. Often are used on desktop or 
      laptop computers for development, testing and other non-production
      purposes. 
	- Easy to use 
	- Ideal for development and testing / convenient
	- Reduced performance (additional layer - host OS)
	- Less secure (host OS) 

- Creates and manages multiple VM's, each with isolateed: 
	- Virtual CPU 
	- Virtual Memory 
	- Virtual Storage 
	- Virtual Network Interfaces 
- Additionally, provides  
    - Memory management 
    - CPU scheduling 
    - Device emulation -- (Managed VMs are then able to run concurrently w/o interference)

- Each managed VM interacts with the virtualized resources/hardware provided by the hypervisor.
  Done so by intercepting hardware requests from the guest OS and translating them into the corresponding actions on hardware and may leverage hardware-assisted virtualization. (Intel VT-x and AMD-V)

- Exs 1: VMware vSphere/ESXi, Microsoft Hyper-V, Xen, KVM (LINUX), Citrix Hypervisor, Proxmox VE, Nutanix AHV, Oracle VM Server
- Exs 2: VMware Workstation (Player), Oracle VM VirtualBox, Parallels Desktop, , Microsoft Virtual PC

======================================================================================================

Cloud computing is a paradigm that leverages virtualization techniques to 
provide users with on-demand access to computing resources over the internet. 
Virtual Machines (VMs) enable multiple isolated operating systems on a single server, 
facilitating efficient resource usage. Containers, exemplified by Docker, package applications 
and dependencies into portable units, simplifying deployment. Unikernels further optimize 
resource usage, making these technologies essential for the cloud's flexibility and efficiency.

- Dedicated VM's:
    - COMPLETE application isolation
    - grants resource HW optimization
    - grants operational flexibility
    - considerable overhead in memory and storage footprint

- Docker/Containers: 
    - Lightweight environments capturing exclusively needed dependencies for applications as well as a minimal runtime environment.
    - Run as user space applications, executing multiple _isolated_ software
    - Share underlying OS and common utilities, eliminating need for component duplicates
    - Fast boot process, low overhead, efficient
    - Security/Privacy concerns due to non-complete isolation.

- Unikernels 
    - Performant (However lacks _real world exhibitions_)
        - Contrast to Monolithic OSes 
            - Protection-domain switches between the application and the kernel might be redundant in a virtualization context because isolation is ensured by the hypervisor, and result in measurable performance degradation.
            - Multiple address spaces may be useless in a single application domain, but removing such support in standard OSes requires a massive reimplementation effort.
            - For RPC-style server applications, threading is not needed, with a single, run-to-completion event loop sufficing for high performance. This would remove the need for a scheduler within the VM and its associated overheads, as well as the mismatch between the guest and hypervisor schedulers.
            - For performance-oriented UDP-based apps, much of the OS networking stack is useless: the app could simply use the driver API, much like DPDK-style applications already do. There is currently no way to easily remove just the network stack but not the entire network sub-system from standard OSes.
            - Direct access to NVMe storage from apps removes the need for file descriptors, a VFS layer and a filesystem, but removing such support from existing OSes, built around layers of the storage API, is very difficult.
            - Memory allocators have a large impact on application performance, and general purpose allocators have been shown to be suboptimal for many apps. It would therefore be ideal if each app could choose its own allocator; this is however very difficult to do in today's operating systems because the allocators that kernels use are baked in.
    - Single purpose appliance linked to library OS (Device drivers, schedulers, network stack) 
    - Immutable and Lightweight images, similarly efficient as containers
    - Booted using hypervisor
    - Improved security
        - When running on type 1 hypervisors, will leverage HW virt. techniques given by the plaftorm
            - since each Unikraft VM runs a single application, cross-application isolation is provided by the hypervisor, resulting in significantly more robust guarantees than processes or Docker containers.
        - Typically no shell access
        - Compile time security checks
        - Immutable and Stateless
        - Specialization, tight coupling between OS and application
        - Reducing dependencies also reduces attack surface

# Slide 2 - Motivation: Unikernels - Cons

- Issues
    - Lack of Maturity/Tooling
        - No shell access
        - Difficult to debug/inspect since traditional tools assume full-fledged OS
    - Limited Observability (directly related to tooling)
    - Limited Ecosystem compared to Containers/VM's
        - Fewer pre-built unikernels and libraries available
    - Operational complexity
    - Porting/Compatability Effort
    - High Barrier to entry / Learning curve 
        - Require significant understanding of underlying components
    - Lack of standardization among projects
    - Lack of widespread use-cases
    - No vendor-backed solutions yet!

# Slide 3 - Motivation: Unikernels - Unikraft

Unikraft has a size comparable with that of a container, while it retains the power of a 
virtual machine, meaning it can directly control the hardware components (virtualized, or not, if running bare-metal).

Unikraft's Framework approach: 
- Library Components. Unikraft modules TODO, each of which provides some piece of functionality. As is expected of a library, they are the core building blocks of an application. Libraries can be arbitrarily small (e.g., a small library providing a proof-of-concept scheduler) or as large as standard libraries like libc. However, libraries in Unikraft often wrap pre-existing libraries, such as openssl, and as such existing applications can still make use of relevant, existing systems without having to re-work anything.

Unikraft libraries are grouped into two large groups: core (or internal) libraries, and external libraries. Core libraries generally provide functionality typically found in operating systems. Such libraries are grouped into categories such as memory allocators, schedulers, filesystems, network stacks and drivers, among others. Core libraries are part of the main Unikraft repo which also contains the build tool and configuration menu.

External libraries consist of existing code not specifically meant for Unikraft. This includes standard libraries such as libc or openssl, but also run-times like Python.

- Configuration. Inspired by Linux's KConfig system, Unikraft uses this approach to quickly and easily allow users to pick and choose which libraries to include in the build process, as well as to configure options for each of them, where available. Like KConfig, the menu keeps track of dependencies and automatically selects them where applicable.
- (Kraftkit) Build Tools. To seamlessly build and manage Unikraft, its components, configuration and its execution is a suite of tools ... core of Unikraft is a suite of tools which aid in the creation of the final unikernel image. Based on GNU Make, it takes care of compiling and linking all the relevant modules and of producing images for the different platforms selected via the configuration menu.

- Unikernels / Unikraft
    - Design: 
        - Single address space: Target single application scenarios, with possibly different applications talking to each other through networked communications.
        - Fully modular system: All components, including operating system primitives, drivers, platform code and libraries should be easy to add and remove as needed; even APIs should be modular.
        - Single protection level: There should be no user-/kernel-space separation to avoid costly processor mode switches. This does not preclude compartmentalization (e.g., of micro-libraries), which can be achieved at reasonable cost.
        - Static linking: Enable compiler features, e.g., Dead-Code Elimination and Link-Time-Optimization (LTO), to automatically get rid of unneeded code.
        - POSIX support: In order to support existing or legacy applications and programming languages while still allowing for specialization under that API.
        - Platform abstraction: Seamless generation of images for a range of different hypervisors/VMMs.
    - Performant - How so?
        - Contrast to Monolithic OSes 
            - Protection-domain switches between the application-kernel might be redundant in a virtualization context because isolation is ensured by the hypervisor, and result in measurable performance degradation.
            - Multiple address spaces may be useless in a single application domain, but removing such support in standard OSes requires a massive reimplementation effort. Display additional overhead w/ mutiple address space management.
            - For RPC-style server applications, threading is not needed, with a single, run-to-completion event loop sufficing for high performance. This would remove the need for a scheduler within the VM and its associated overheads, as well as the mismatch between the guest and hypervisor schedulers.
            - For performance-oriented UDP-based apps, much of the OS networking stack is useless: the app could simply use the driver API, much like DPDK-style applications already do. There is currently no way to easily remove just the network stack but not the entire network sub-system from standard OSes.
            - Direct access to NVMe storage from apps removes the need for file descriptors, a VFS layer and a filesystem, but removing such support from existing OSes, built around layers of the storage API, is very difficult.
            - Memory allocators have a large impact on application performance, and general purpose allocators have been shown to be suboptimal for many apps. It would therefore be ideal if each app could choose its own allocator; this is however very difficult to do in today's operating systems because the allocators that kernels use are baked in.
    - Single purpose appliance linked to library OS (Device drivers, schedulers, network stack) 
    - Immutable and Lightweight images, similarly efficient as containers
    - Booted using hypervisor
    - Improved security
        - When running on type 1 hypervisors, will leverage HW virt. techniques given by the plaftorm
            - since each Unikraft VM runs a single application, cross-application isolation is provided by the hypervisor, resulting in significantly more robust guarantees than processes or Docker containers.
        - Typically no shell access
        - Compile time security checks
        - Immutable and Stateless
        - Specialization, tight coupling between OS and application
        - Reducing dependencies also reduces attack surface


# Slide 4 - Unikraft + Kraftkit

Kraftkit:
Go-based framework for building custom, minimal, immutable lightweight unikernel virtual machines based on Unikraft. 
Based on Go, GNU Make, C and KConfig, it takes care of compiling and linking all the relevant modules and of producing images for the different platforms selected via the configuration menu.

Unikraft's Framework approach: 
- Library Components. Unikraft modules TODO, each of which provides some piece of functionality. As is expected of a library, they are the core building blocks of an application. Libraries can be arbitrarily small (e.g., a small library providing a proof-of-concept scheduler) or as large as standard libraries like libc. However, libraries in Unikraft often wrap pre-existing libraries, such as openssl, and as such existing applications can still make use of relevant, existing systems without having to re-work anything.

Unikraft libraries are grouped into two large groups: core (or internal) libraries, and external libraries. Core libraries generally provide functionality typically found in operating systems. Such libraries are grouped into categories such as memory allocators, schedulers, filesystems, network stacks and drivers, among others. Core libraries are part of the main Unikraft repo which also contains the build tool and configuration menu.

External libraries consist of existing code not specifically meant for Unikraft. This includes standard libraries such as libc or openssl, but also run-times like Python.

- Configuration. Inspired by Linux's KConfig system, Unikraft uses this approach to quickly and easily allow users to pick and choose which libraries to include in the build process, as well as to configure options for each of them, where available. Like KConfig, the menu keeps track of dependencies and automatically selects them where applicable.
- (Kraftkit) Build Tools. To seamlessly build and manage Unikraft, its components, configuration and its execution is a suite of tools ... core of Unikraft is a suite of tools which aid in the creation of the final unikernel image. Based on GNU Make, it takes care of compiling and linking all the relevant modules and of producing images for the different platforms selected via the configuration menu.
