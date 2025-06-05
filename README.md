[![AWQP Logo](./figures/AWQP_horizontal_rounded.png)](https://waterquality.colostate.edu)

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.14003999.svg)](https://doi.org/10.5281/zenodo.14003999)

# AWQP Low-Cost IoT Water Sampler
A low-cost, automated water sampler (LCS) with Internet of Things (IoT) technology for scalable, near-real-time water quality research developed by the Colorado State University Agricultural Water Quality Program (AWQP).

> [!NOTE]
> This project is actively under development. Code, parts, instructions, and other content are subject to change as we enhance the LCS. If you download/clone/fork this repository, we ask that you **please [email us directly](mailto:ansley.brown@colostate.edu;e.deleon@colostate.edu;erik.wardle@colostate.edu?subject=Inquiry%20about%20the%20Low%20Cost%20IoT%20Water%20Sampler%20from%20GitHub)** for the most up-to-date information and resources. We will also email you with any news related to the project moving forward!

## Table of Contents
- [Why create a low-cost water sampler?](#why-create-a-low-cost-water-sampler?)
- [Repo Contents](folder-contents)
- [Low Cost Sampler Description](#low-cost-sampler-description)
- [3D prints](#3D-prints)
- [Parts List](#parts-list)
- [How-to guide](#how-to-guide)
- [Known Bugs](#known-bugs)
- [Future Developments](#future-developments)
- [How to Cite](#how-to-cite)
- [License](#license)

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
scalable research. To address this need, the [Colorado State University Agricultural Water Quality
Program (AWQP)](https://waterquality.colostate.edu) has developed a low-cost, automated water sampler (LCS) with Internet of
Things (IoT) technology for scalable, near-real-time water quality research. This work directly
follows deliverables from an awarded NRCS Conservation Innovation Grant titled, “Next
Generation Technology for Monitoring Edge-of-Field Water Quality in Organic Agriculture”. The
CSU AWQP intends to create additional research and regulation opportunities for Colorado and beyond using this technology.

![a deployed water sampler](./figures/Intro-min.JPG)
**Figure 1.** Image of the low-cost automated water sampler (LCS) deployed at a mountain meadow hay field near Steamboat Springs, Colorado.

To learn more about AWQP, please visit [the AWQP website](https://waterquality.colostate.edu).

## Repo Contents
- .vscode
    - settings for flashing in VS code using the particle workbench add-on.
- compiled-firmwares
    - previously compiled firmwares for various borons (current code requires a unique binary for each device to accomodate for individual e-tape calibration)
- figures
    - figures embedded into README.md
- files
    - 3D prints: contains .STL files for printing that required for assembly
    - Bill of Materials: Excel with BOM, links, and prices 
- lib
    - libraries used in source code
- src
    - source code for particle boron flashing
    - config.h template for storing sensitive information like API keys and device-specific information needed to operate the LCS
- target
    - available firmware targets for particle devices
- .gitignore
    - files and folders to ignore when committing to the repository (e.g., config.h)
- AUTHORS.md
    - list of authors and contributors to the project
- CITATION.cff
    - citation file for the project, please use this to cite the LCS in your work
- CODE_OF_CONDUCT.md
    - code of conduct for the project, please read before contributing
- CONTRIBUTING.md
    - guidelines for contributing to the project, please read before contributing
- LICENSE.md
    - licensed under GNU General Public License Version 2 (GNU GPL V2.0)
- project.properties
    - contains project code and library dependencies
    
## Low Cost Sampler Description
The AWQP-developed LCS is comprised of five main components as shown in Figure 2: 1) device control panel 2) power assembly 3) pump assembly 4) a water depth sensor (eTape, MileOne), and 5) the water storage apparatus. 

![low-cost sampler image](./figures/Hardware_description.png)
**Figure 2.** Picture of the low-cost automated water sampler (LCS) deployed in-situ, with its primary components annotated


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
**Figure 3.** Results from a preliminary flow comparison study between the LCS and commercial Teledyne ISCO 6712 automated sampler.

## Software
- Particle Account and Particle Workbench on Virtual Studio Code is needed to claim a Particle Boron and flash calibration and sampler code.  
- Blynk IoT controls and monitors the LCS remotely via phone app. 
- (optional) Ubidots offers storage and visualization of sampler data. 

## 3D-prints
Can be found on our [AWQP Printables page](https://printables.com/@AgWaterQuality_66019):
* [Peristaltic pump mount](https://printables.com/model/560168-mount-for-a-peristaltic-pump)
* [12v Battery  mount](https://printables.com/model/560141-awqp-12v-battery-mount-for-the-low-cost-sampler)
* [Solar Controller Mount](https://www.printables.com/model/1177165-solar-controller-huine-mount-for-low-cost-iot-wate)
* [eTape TPU Cover](https://www.printables.com/model/1177200-milone-etape-tpu-protective-cover-for-awpq-low-cos) 

## Bill of Materials 
Please [contact the AWQP](mailto:ansley.brown@colostate.edu;e.deleon@colostate.edu;erik.wardle@colostate.edu?subject=Inquiry%20about%20the%20Low%20Cost%20IoT%20Water%20Sampler%20from%20GitHub) for the most current part list; these are often changing and being updated as improvements get implemented!

Current list updated 03 Jun. 2025:

[Bill of Materials](files/Bill%20of%20Materials.xlsx) 

## How-to guide
Introduction to major hardware components with a brief description:

- Enclosure: Protects the sampler components from the environment
- Pump Assembly: a peristaltic pump to collect water samples 
    - DRV8825 Motor Driver: Controls peristaltic pump with precision and efficiency
    - Non-contact water sensor: Detects water priming the pump
- Power Assembly: 12-volt Battery 
    - Solar Panel (10W): Charges Battery 
    - Solar Charging/Controller: Regulates power from the solar panel to the battery 
- Device Control Unit: PCB Carrier for the Particle Boron Microprocessor and all sensor connection points
- Water Depth Sensor: Using a eTape Water Level Sensor to monitor water level in flumes or streams. 
    - **Note:** For outdoors used  the sturdy eTape cable directly from the manufacturer, Milone Technologies.
- Water Storage Apparatus: Holds sample bottles and keeps collected samples cool. 


Brief Overview: 

1. Purchase all necessary hardware components (see [Bill of Materials](/files/Bill%20of%20Materials.xlsx))
2. 3D-print necessary mounting parts
3. Assemble hardware - [Here's our video guide!](https://youtu.be/WXuII_zaUJU?si=he2FRvl1eTsFYpLh)

[![low cost sampler installation video](./figures/youtube_img.JPG)](https://youtu.be/WXuII_zaUJU?si=he2FRvl1eTsFYpLh)

<br>  **Device Control Panel:** 

<img src="./figures/PCB_Guide.png" alt="PCB Guide" width="65%" />
<img src="./figures/PCB_complete_back.jpg" alt="PCB Guide" width="65%" />    

**Figure 4.** Device Control Panel:  PCB front and back with wiring connection layouts and labels 

<br>

4. Make Blynk account and install Blynk phone application - [Bynk application website](https://blynk.io/)

The LCS requires user inputs to program the sampling protocol. These inputs include Volume to Sample (mL), Sampling Interval (min), Threshold (cm), Sample Bottle (mL). Using Blynk, users will input how much volume to collect (max 700mL per sample interval), how often to sample in minutes, the threshold depth in centimeters that will activate your sampler to start collecting water, and how large is the sample bottle to prevent sample slipovers.

- Setup Template 
- Add the following Datastreams as virtual pins 

<br>

| Name              | Virtual Pin | Data Type | Unit   | Min-Max    | Default |
|:-----------------:|:-------------:|:-----------:|:--------:|:------------:|:---------:|
| mL to Sample      | V1          | Integer   | (mL)   | 0 - 700   | 200     |
| Terminal Status   | V2          | String    |        |            |         |
| Sample Interval   | V3          | Integer   | (min)  | 0 - 720    | 60      |
| Threshold         | V4          | Integer   | (cm)   | 0 - 100    | 100     |
| Sample Bottle     | V5          | Integer   | (mL)   | 0 - 10000  | 2000    |
| Sample Now        | V9          | Integer   |        |            |         |
| mL to Collect     | V12         | Integer   | (mL)   | 0 - 1000   | na      |
| Current Threshold | V14         | Integer   | (cm)   | 0 - 100    | na      |
| Current Depth     | V17         | Integer   | (cm)   | 0 - 100    | na      |

<br>

5. (optional) Make Ubidots account - [Ubidots website](https://industrial.ubidots.com/)
6. eTape and Pump Calibration

    - eTape Calibration [Repo](https://github.com/CSU-Agricultural-Water-Quality-Program/AWQP-LCS-Etape-Calibration/tree/main) 
    - Pump Calibrtion [Repo](https://github.com/CSU-Agricultural-Water-Quality-Program/AWQP_LCS_pump_calibration)

7. Flash code from this repo, after updating the `config.h` file with your TOKENs from Blynk and Ubidots
8. Use the Blynk app to program your sampler 
9. Deploy and Enjoy!

### Configuration file instructions

For the code to run properly, you'll need to set up a `config.h` file with your API keys and other configurations.

1. **Navigate to the `src` directory**:
   - Inside the `src` directory, you will find a template file named `config_template.h`.

2. **Duplicate and Rename**:
   - Copy the `config_template.h` and rename the copied file to `config.h`.

3. **Add Your API tokens for Ubidots and Bylnk**:
   - Open `config.h` with a text editor of your choice. Replace the placeholders like `"YOUR_API_KEY_HERE"` with your actual API keys or other configuration details.

4. **Save and Close**:
   - After adding your details, save and close the file. Now your code should be able to run with your specific configurations.

> [!WARNING]
> Never commit your `config.h` with your actual API keys or Tokens to public repositories to ensure the privacy of your keys!

## Known bugs
- The water detection sensor is unreliable in its current state; we are not sure if this is a hardware or software issue at the moment. Currenlty working on fix. This does not affect the sampling process, but it does mean that the pump may not prime properly if the water detection sensor fails to detect water in the hose.
- In outdoor deployment, the normal wired Etape readings can bounce, leading to unintentional sampling. This bounce has not been observed in the strudier wired Etape specially requested with the TPU cover. We highly recommended to request the sturdy eTape cable directly from the manufacturer.
    - we tend to leave the trigger point at an unrealistically high number (e.g., 1000cm) until the device *should* be sampling, then we move it down to a realistic number (e.g., 2cm)
- Etape sensors only begin to accurately read depth at the 1" mark on the device
    - this is a hardware issue, and cannot be fixed in software
    - to circumvent this, we place the etape at -1" depths in the deployed stilling wells or other water bodies to ensure an accurate reading, then subtract 1" off of readings in post-processing for flow calculations.

## Latest updates
- v1.00 - Initial Release - Rough program outline with serial monitor// interface
- v1.01 - First Working Version, debugged with keyboard input of sample volume
- v1.02 - Uses Blynk  and WiFi for input and reporting instead of keyboard IDE
- v1.03 - Add stats and other Blynk features, provisions for prepurge of hose
- v1.04 - add a secound pump to the code
- v1.05 - coverted to particle using workbench
- v1.06 - added etape
- V1.07 - moved to new blynk IoT
- V1.08 - cleaned, added variable, add temp resistance to etapeand add project to private github repo
- V1.09 - added remote reset function
- V1.10 - added config.h file to store sensitive info and device speicific info
- V1.2 - fixed config.h file and updates bill of materials
- V1.21 - Added images, pinout, and blynk datastreams to the How To section
- V1.3 - Cleaned up code for Hardware X article release, commented out Ubidots code since it is optional, updated config.h file

## Future Developments
- Integrate a "time until next sampling" variable that can be called or sent at each payload
- make e-tape calibration coeficcients either a dictionary and/or a particle variable to alleviate the need for tailored binaries to flash each device.  Ultimately, this would allow users to make the device a particle product and enable fleet flashing.
- if the water detection sensor continues to fail we will add a "tube length" variable in the blynk app to calculate water needed to prime the pump prior to sampling.
- compare etape calibration data to see if a universal calibration equation can be developed for each etape length instead of having individual calibration equations for each device
- include firmware to add *in situ* water quality sensor like pH and turbidity 

## How to Cite

If you use the AWQP Low-Cost IoT Water Sampler (LCS) in your research or if it proves helpful in your work, please consider citing it. a [CITATION.cff](CITATION.cff) file is provided, or you can use the following BibTeX entry:

```bibtex
@misc{awqp_lcs_2024_v2,
  author       = {Emmanuel Deleon and Ansley Brown and Erik Wardle and Troy Bauder and Dylan Casey and Jay Ham and Mark Uchanski},
  title        = {{Low-Cost IoT Water Sampler}},
  month        = oct,
  year         = 2024,
  note         = {Version 1.2},
  doi          = {10.5281/zenodo.14003999},
  publisher    = {Zenodo},
  url          = {https://zenodo.org/doi/10.5281/zenodo.14003999}
}
```

## License
This project is licensed under the GNU GENERAL PUBLIC LICENSE Version 2 (GNU GPL V2.0) - see the [LICENSE.md](LICENSE.md) file for details.

**Please visit [CSU STRATA's website](https://csustrata.org/technology-transfer/available-technology/low-cost-automated-water-sampler/) to inquire about a permissive commercial license for this project, and use the [contact form on that page](https://csustrata.org/technology-contact-2024-035/) for initiating that discussion.**

Copyright © 2023 Colorado State University Agricultural Water Quality Program. All rights reserved.