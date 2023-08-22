# low-cost-iot-water-sampler
A low-cost, automated water sampler (LCS) with Internet of Things (IoT) technology for scalable, near-real-time water quality research developed by the Colorado State University Agricultural Water Quality Program

## Table of Contents
- [Why create a low-cost water sampler?](#why-create-a-low-cost-water-sampler?)
- [Repo Contents](folder-contents)
- [Low Cost Sampler Description](#low-cost-sampler-description)
- [3d prints](#3d-prints)
- [Parts List](#parts-list)
- [Known Bugs](#known-bugs)
- [Future Developments](#future-developments)

---

## Why create a low-cost water sampler?
In Colorado and across the United States, agriculture is being identified as one source of nutrient
pollution in State and Federal waters. Nutrients such as nitrogen and phosphorus run off
farmlands and accumulate in surface waterways, causing water quality issues. Although
agricultural nonpoint sources are not currently regulated in Colorado, initiatives are set up to
encourage the adoption of Best Management Practices (BMPs) that protect surface water quality.
Quantifying BMP impacts on water quality, requires robust, edge-of-field (EoF) monitoring
systems that can accurately measure flow and collect water for nutrient and sediment analysis.
NRCS EoF standards currently require equipment that is often too costly for pragmatic and
scalable research. To address this need, the Colorado State University Agricultural Water Quality
Program (AWQP) has developed a low-cost, automated water sampler (LCS) with Internet of
Things (IoT) technology for scalable, near-real-time water quality research. This work directly
follows deliverables from an awarded NRCS Conservation Innovation Grant titled, “Next
Generation Technology for Monitoring Edge-of-Field Water Quality in Organic Agriculture”. The
CSU AWQP intends to create additional research and regulation opportunities for Colorado and beyond using this technology.

To learn more about AWQP, please visit [the AWQP website](https://waterquality.colostate.edu).

## Repo Contents
- .vscode
    - settings for flashing in VS code using the particle workbench add-on.
- 3d-prints
    - contains .STL files for printing required assembly parts on a 3d-printer
- compiled-firmwares
    - previously compiled firmwares for various borons (current code requires a unique binary for each device to accomodate for individual e-tape calibration)
- figures
    - figures embedded into README.md
- lib
    - libraries used in source code
- src
    - source code for particle boron flashing
- target
    - available firmware targets for particle devices
- project.properties
    - contains project code and library dependencies

## Low Cost Sampler Description
The AWQP-developed LCS is comprised of six main components as shown in Figure 1: 1) a
cellular-enabled microcontroller, 2) a 12V battery and solar charger, 3) a peristaltic pump with
tubing for water sample collection, 4) a 12V, 10W solar panel, 5) a water depth detecting sensor
and, 6) a cooler for sample preservation.

![low-cost sampler image](./figures/LCS.png)
**Figure 1.** Picture of the low-cost automated water sampler (LCS) deployed in-situ, with its primary components annotated: 1) a cellular-enabled microcontroller, 2) a 12 V battery and solar charger, 3) a peristaltic pump with tubing, 4) a X V, X W solar panel, 5) a water depth detecting sensor, and 6) a cooler.


Like commercial models, the LCS can detect and measure water flow in an installed flume via
depth, sample water at pre-determined or user-triggered intervals (in this case, hourly), preserve
water samples for later collection, remote data monitoring through cellular communications, and
stay powered remotely through solar and battery means. However, the LCS model accomplishes
this at approximately 1/10th of the cost of a commercial apparatus ($700-1,000). Additionally,
commercial models require the additional purchase of a cellular modem for wireless
connectivity, whereas the LCS integrally incorporates it into the microcontroller itself. Upon
completion of this experiment, the AWQP intends to open-source the LCS for future
collaborative development and sharing via GitHub repository on the AWQP GitHub
organization.


A preliminary comparison study performed by the AWQP indicate strong agreement between
LCS depth measurements and commercial bubbler units, with a root mean squared error (RMSE)
of 4.2 mm (n=1099). Additionally, measured analyte concentrations (total suspended solids,
NO3, NO2, Total N, Orthophosphate, Total Phosphorous) were similar, but lacked enough
sample points to accurately make a comparison. An example runoff depth measurement
comparison from an irrigation event at a corn field in Fort Collins, CO in 2020 is shown in
Figure 2.

![flow comparison graph](./figures/flowComparison.png)
**Figure 2.** Results from a preliminary flow comparison study between the LCS and commercial Teledyne ISCO 6712 automated sampler.

## 3d-prints
As found on our [AWQP Printables page](https://www.printables.com/@AgWaterQuality_66019):
* [Peristaltic pump mount](https://www.printables.com/model/560168-mount-for-a-peristaltic-pump)
* [12v alkaline battery and solar charger mount](https://www.printables.com/model/560141-awqp-12v-battery-mount-for-the-low-cost-sampler)

## Parts List
Coming soon!

## Known bugs
Coming soon!

## Future Developments
- Integrate a "time until next sampling" variable that can be called or sent at each payload
- add remote reset function to allow the user to reset the particle boron microcontroller remotely
- make e-tape calibration coeficcients either a dictionary and/or a particle variable to alleviate the need for tailored binaries to flash each device.  Ultimately, this would allow users to make the device a particle product and enable fleet flashing.