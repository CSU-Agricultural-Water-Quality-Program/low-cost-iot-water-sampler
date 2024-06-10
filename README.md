[![AWQP Logo](./figures/AWQP_horizontal_rounded.png)](https://waterquality.colostate.edu)

[![DOI](https://zenodo.org/badge/681357586.svg)](https://zenodo.org/doi/10.5281/zenodo.10257622)

# Low-Cost IoT Water Sampler
A low-cost, automated water sampler (LCS) with Internet of Things (IoT) technology for scalable, near-real-time water quality research developed by the Colorado State University Agricultural Water Quality Program (AWQP).

> [!NOTE]
> This project is actively under development. Code, parts, instructions, and other content are subject to change as we enhance the LCS. If you download/clone/fork this repository, we ask that you **please [email us directly](mailto:ansley.brown@colostate.edu;e.deleon@colostate.edu;erik.wardle@colostate.edu?subject=Inquiry%20about%20the%20Low%20Cost%20IoT%20Water%20Sampler%20from%20GitHub)** for the most up-to-date information and resources. We will also email you with any news related to the project moving forward!

## Table of Contents
- [Why create a low-cost water sampler?](#why-create-a-low-cost-water-sampler?)
- [Repo Contents](folder-contents)
- [Low Cost Sampler Description](#low-cost-sampler-description)
- [3d prints](#3d-prints)
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
The AWQP-developed LCS is comprised of six main components as shown in Figure 2: 1) a
cellular-enabled microcontroller, 2) a 12V battery and solar charger, 3) a peristaltic pump with
tubing for water sample collection, 4) a 12V, 10W solar panel, 5) a water depth detecting sensor
and, 6) a cooler for sample preservation.

![low-cost sampler image](./figures/LCS.png)
**Figure 2.** Picture of the low-cost automated water sampler (LCS) deployed in-situ, with its primary components annotated: 1) a cellular-enabled microcontroller, 2) a 12 V battery and solar charger, 3) a peristaltic pump with tubing, 4) a 12 V, 10 W solar panel, 5) a water depth detecting sensor, and 6) a cooler for sample preservation.


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

## 3d-prints
As found on our [AWQP Printables page](https://printables.com/@AgWaterQuality_66019):
* [Peristaltic pump mount](https://printables.com/model/560168-mount-for-a-peristaltic-pump)
* [12v alkaline battery and solar charger mount](https://printables.com/model/560141-awqp-12v-battery-mount-for-the-low-cost-sampler)

## Parts List
Please [contact the AWQP](mailto:ansley.brown@colostate.edu;e.deleon@colostate.edu;erik.wardle@colostate.edu?subject=Inquiry%20about%20the%20Low%20Cost%20IoT%20Water%20Sampler%20from%20GitHub) for the most current part list; these are often changing and being updated as improvements get implemented!

Current list updated 4 December 2023:

| Part Name                                                        | Part Type                 | Cost per Unit | Est # Per Sampler | Total Cost per Box | Link                                                                                                    |
|------------------------------------------------------------------|---------------------------|---------------|-------------------|---------------------|---------------------------------------------------------------------------------------------------------|
| 6-30V Large Flow Dosing Pump Peristaltic Pump for Vacuum...     | Peristaltic Pump          | $44.69        | 1                 | $44.69              | [Amazon](https://www.amazon.com/gp/product/B082K6CYV1/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)  |
| ExpertPower 12V 7 Amp EXP1270 Rechargeable Lead Acid Battery    | Battery                   | $18.00        | 1                 | $18.00              | [Amazon](https://www.amazon.com/ExpertPower-EXP1270-Rechargeable-Lead-Battery/dp/B003S1RQ2S/ref=sr_1_4?keywords=12v%2Bbattery&qid=1578353558&sr=8-4&th=1) |
| Morningstar SS-6-12V Sunsaver-6 Amp                             | Solar Power Controller    | $75.00        | 1                 | $75.00              | [Amazon](https://www.amazon.com/gp/product/B00BQZZB2A/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) |
| Particle Boron LTE North America                                | Microprocessor            | $53.00        | 1                 | $53.00              | [Particle](https://store.particle.io/collections/cellular/products/boron-lte)                         |
| PCB board                                                        | PCB Board                  | $20.00        | 1                 | $20.00              | [Amazon](https://www.amazon.com/gp/product/B07ZV8BKNF/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)  |
| DRV8825 Stepper Motor Driver Carrier, High Current               | Pump Driver                | $8.95         | 1                 | $8.95               | [Pololu](https://pololu.com/product/2133)                                                              |
| Stepper Motor Driver Shield Expansion Board DRV8825/A4988        | Pump Driver Mount          | $8.00         | 1                 | $8.00               | [Amazon](https://www.amazon.com/gp/product/B08RP2SCJ7/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) |
| Pololu 5V, 1A Step-Down Voltage Regulator D24V10F5               | Voltage Regulator          | $7.49         | 1                 | $7.49               | [Pololu](https://www.pololu.com/product/2831)                                                           |
| 18" Standard eTape® Assembly                                     | Water Level               | $59.99        | 1                 | $59.99              | [MiloneTech](https://milonetech.com/products/standard-etape-assembly)                                  |
| Non-Contact Water Level Sensor Capacitive Liquid Level Detector | Liquid Sensor             | $8.29         | 1                 | $8.29               | [Amazon](https://www.amazon.com/gp/product/B0832YDTPX/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) |
| Altelix 14x12x8 Fiberglass Weatherproof NEMA 4X Enclosure...    | Electronic Enclosure       | $70.00        | 1                 | $70.00              | [Amazon](https://www.amazon.com/gp/product/B07KW14VH9/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) |
| Cable Gland 100 Pack PG7 Waterproof                             | Glands                    | $0.50         | 12                | $6.00               | [Amazon](https://www.amazon.com/gp/product/B09X4GK3FT/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) |
| 12V Male+Female 2.1x5.5MM DC Power Jack Plug                   | Power Plugs               | $8.00         | 1                 | $8.00               | [Amazon](https://www.amazon.com/gp/product/B01J1WZENK/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) |
| Cooler                                                           | Bottle Enclosure          | $99.00        | 1                 | $99.00              | [Amazon](https://www.amazon.com/gp/product/B0B4X57WZY/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) |
| 2.54mm Spacing Female 16 Pins PCB                                | Feather Board Pins        | $8.00         | 1                 | $8.00               | [Amazon](https://www.amazon.com/gp/product/B07HCCTY94/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) |
| 2.54mm Pitch 12 Terminals Straight Header                        | Feather Board Pins        | $8.00         | 1                 | $8.00               | [Amazon](https://www.amazon.com/gp/product/B07PVY4D52/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) |
| Wire, Tubing, Adhesives, and other Misc Supplies                 |                           | $50.00        | 1                 | $50.00              |                                                                                                         |
| Bulkhead 1/4″ Straight Adapter 1/4″ ID x 1/4″ ID in Medical...  | Tubing Adapter            | $2.00         | 2                 | $4.00               | [Eldon James](https://eldonjames.com/product/bh4s-4-4mn-qc/)                                           |
| PVC Tubing 1/4"ID X 3/8"OD Flexible Clear Vinyl Hose 100 Feet... | Tubing                    |               |                   |                     | [Amazon](https://www.amazon.com/gp/product/B07WCM9B9H/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)   |
| Beduan Pneumatic Plastic Bulkhead Union Fitting 6mm Tube OD x 6mm | Bulkhead Fitting           | $10.98        | 1                 | $10.98              | [Amazon](https://www.amazon.com/gp/product/B07MLL1TNP/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)    |
| Bottles                                                          | 2L Bottle                 | $30.00        | 2                 | $60.00              | [US Plastic](https://www.usplastic.com/catalog/item.aspx?itemid=34227&v1=&v7=&gad_source=1&gclid=Cj0KCQiAgqGrBhDtARIsAM5s0_lNtdxKP6RPs_ngv4Kppt8AFrtlITrcvWsjd5ZQKeNmv4hUJ4Kuh4waAuoAEALw_wcB)
| 12 Volt Solar Panel                                               | Solar Panel               | $25.00        | 1                 | $25.00              | [Amazon](https://www.amazon.com/gp/product/B00OZC3X1C/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1)   |
|                                           |                       | **Estimated Total**       | **$652.39**   |                   |                     |


## How-to guide
More coming soon!
1. Purchase all necessary hardware components 
2. 3D-print necessary mounting parts
3. Assemble hardware - [Here's our video guide!](https://youtu.be/WXuII_zaUJU?si=he2FRvl1eTsFYpLh)

[![low cost sampler installation video](./figures/youtube_img.JPG)](https://youtu.be/WXuII_zaUJU?si=he2FRvl1eTsFYpLh)

4. Install Blynk phone application - [Bynk application website](https://blynk.io/)
5. Make Ubidots account - [Ubidots website](https://industrial.ubidots.com/)
6. Flash code from this repo, after updating the `config.h` file with your TOKENs from Blynk and Ubidots
7. To be continued...

### Configuration file instructions

For the code to run properly, you'll need to set up a `config.h` file with your API keys and other configurations.

1. **Navigate to the `src` directory**:
   - Inside the `src` directory, you will find a template file named `config_template.h`.

2. **Duplicate and Rename**:
   - Copy the `config_template.h` and rename the copied file to `config.h`.

3. **Add Your API Keys and/or tokens**:
   - Open `config.h` with a text editor of your choice. Replace the placeholders like `"YOUR_API_KEY_HERE"` with your actual API keys or other configuration details.

4. **Save and Close**:
   - After adding your details, save and close the file. Now your code should be able to run with your specific configurations.

> [!WARNING]
> Never commit your `config.h` with your actual API keys or Tokens to public repositories to ensure the privacy of your keys!

## Known bugs
- The water detection sensor is unreliable in its current state; we are not sure if this is a hardware or software issue at the moment
- Etape readings can bounce, leading to unintentional sampling
    - we tend to leave the trigger point at an unrealistically high number until the device *should* be sampling, then we move it down to a realistic number (e.g., 2cm)
- Etape sensors only begin to accurately read depth at the 2" mark on the device
    - this is a hardware issue ongoing at Mileone
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

## Future Developments
- Integrate a "time until next sampling" variable that can be called or sent at each payload
- make e-tape calibration coeficcients either a dictionary and/or a particle variable to alleviate the need for tailored binaries to flash each device.  Ultimately, this would allow users to make the device a particle product and enable fleet flashing.
- add a "tube length" variable in the blynk app to calculate water needed to prime the pump prior to sampling.
- compare etape calibration data to see if a universal calibration equation can be developed instead of having individual calibration equations for each device

## How to Cite

If you use the AWQP Low-Cost IoT Water Sampler (LCS) in your research or if it proves helpful in your work, please consider citing it. a [CITATION.cff](CITATION.cff) file is provided, or you can use the following BibTeX entry:

```bibtex
@misc{awqp_lcs_2023,
  author       = {Ansley Brown and Emmanuel Deleon and Erik Wardle and Troy Bauder and Dylan Casey and Jay Ham and Mark Uchanski},
  title        = {{Low-Cost IoT Water Sampler}},
  month        = nov,
  year         = 2023,
  note         = {Version 1.10},
  doi          = {10.5281/zenodo.10257622},
  publisher    = {Zenodo},
  url          = {https://zenodo.org/doi/10.5281/zenodo.10257622}
}
```

## License
This project is licensed under the GNU GENERAL PUBLIC LICENSE Version 2 (GNU GPL V2.0) - see the [LICENSE.md](LICENSE.md) file for details.

**Please visit [CSU STRATA's website](https://csustrata.org/technology-transfer/available-technology/low-cost-automated-water-sampler/) to inquire about a permissive commercial license for this project, and use the [contact form on that page](https://csustrata.org/technology-contact-2024-035/) for initiating that discussion.**

Copyright © 2023 Colorado State University Agricultural Water Quality Program. All rights reserved.