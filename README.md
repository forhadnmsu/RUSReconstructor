## Goal
The goal of this `DimuAnaRUS` module is to get the input data from a ROOT file (in DST format) and convert them into RUS (ROOT Universal Structure) format. This includes triggers, hits, true/reconstructed track or dimuon information, and event details. It supports a wide range of data formats such as integers, doubles, and booleans, and can store this data in flat, vector, or array formats.

# Updated Variable Names and Types
## Event-Level Variables
| Variable Name      | Type               | Description                          |   
|--------------------|--------------------|--------------------------------------|
| `runID`            | `int`              | Identifier for the current run       |   
| `spillID`          | `int`              | Identifier for the spill in the run  |
| `eventID`          | `int`              | Unique identifier for the event      |   
| `rfID`             | `int`              | Identifier for the RF                |   
| `turnID`           | `int`              | Identifier for the Turn                |   
| `fpgaTrigger`      | `int[5]`           | Array of FPGA trigger                |   
| `nimTrigger`       | `int[5]`           | Array of NIM trigger                 |   
| `rfIntensity`      | `int[33]`          | Array for QIE RF intensities         |   

## Hit-Level Variables
| Variable Name          | Type                     | Description                                  |   
|------------------------|--------------------------|----------------------------------------------|
| `hitID`                | `std::vector<int>`       | Hit IDs for all hits                         |   
| `hit_trackID`          | `std::vector<int>`       | Track IDs for all hits                         |   
| `processID`            | `std::vector<int>`       | Track IDs for all hits                         |   
| `detectorID`           | `std::vector<int>`       | Detector IDs for all hits                    |   
| `elementID`            | `std::vector<int>`       | Element IDs associated with each hit         |   
| `driftDistance`        | `std::vector<double>`    | Drift distances for each hit                 |   
| `tdcTime`              | `std::vector<double>`    | TDC timing values for each hit               |   

## Monte Carlo Truth-Level Variables
| Variable Name  | Type                  | Description                                |
|---------------|----------------------|----------------------------------------------|
| `gCharge`    | `std::vector<int>`    | Charges of the Monte Carlo tracks            |
| `gvx`        | `std::vector<double>` | X-coordinate of the generated track vertex   |
| `gvy`        | `std::vector<double>` | Y-coordinate of the generated track vertex   |
| `gvz`        | `std::vector<double>` | Z-coordinate of the generated track vertex   |
| `gpx`        | `std::vector<double>` | X-component of the momentum at the vertex    |
| `gpy`        | `std::vector<double>` | Y-component of the momentum at the vertex    |
| `gpz`        | `std::vector<double>` | Z-component of the momentum at the vertex    |
| `gx_st1`     | `std::vector<double>` | X-coordinate at station 1                    |
| `gy_st1`     | `std::vector<double>` | Y-coordinate at station 1                    |
| `gz_st1`     | `std::vector<double>` | Z-coordinate at station 1                    |
| `gpx_st1`    | `std::vector<double>` | X-component of momentum at station 1         |
| `gpy_st1`    | `std::vector<double>` | Y-component of momentum at station 1         |
| `gpz_st1`    | `std::vector<double>` | Z-component of momentum at station 1         |
| `gx_st3`     | `std::vector<double>` | X-coordinate at station 3                    |
| `gy_st3`     | `std::vector<double>` | Y-coordinate at station 3                    |
| `gz_st3`     | `std::vector<double>` | Z-coordinate at station 3                    |
| `gpx_st3`    | `std::vector<double>` | X-component of momentum at station 3         |
| `gpy_st3`    | `std::vector<double>` | Y-component of momentum at station 3         |
| `gpz_st3`    | `std::vector<double>` | Z-component of momentum at station 3         |

## Reconstructed Dimuon Variables
These variables store information about reconstructed dimuons (`mu+ mu-` pairs), will be obtained from the `SRecDimuon` class, at the default vertex, target (`tgt`), and dump (`dump`) regions.

| Variable Name        | Type                  | Description                                                                      | User Functions                      |
|----------------------|-----------------------|----------------------------------------------------------------------------------|-------------------------------------|
| `rec_dimuon_id`      | `std::vector<int>`    | List of dimuon IDs.                                                              | `SRecDimuon::get_dimuon_id()`       |
|`rec_dimuon_true_id`  | `std::vector<int>`    | List of reconstructed dimuon IDs only when the true dimuon exists.               | `SRecDimuon::get_rec_dimuon_id()`   |
| `rec_track_id_pos`   | `std::vector<int>`    | Track ID of the positive muon track (returns the index of rhe `SRecTrack`).      | `SRecDimuon::get_track_id_pos()`    |
| `rec_track_id_neg`   | `std::vector<int>`    | Track ID of the negative muon track (returns the index of rhe `SRecTrack`).      | `SRecDimuon::get_track_id_neg()`    |
| `rec_px_pos`         | `std::vector<double>` | x-component of the momentum of the vertexed (default) positive muon of the dimuon| `SRecDimuon::get_mom_pos().Px()`    |
| `rec_py_pos`         | `std::vector<double>` | y-component of the momentum of the vertexed (default) positive muon of the dimuon| `SRecDimuon::get_mom_pos().PY()`    |
| `rec_pz_pos`         | `std::vector<double>` | z-component of the momentum of the vertexed (default) positive muon of the dimuon| `SRecDimuon::get_mom_pos().Pz()`    |
| `rec_px_neg`         | `std::vector<double>` | x-component of the momentum of the vertexed (default) negative muon of the dimuon| `SRecDimuon::get_mom_neg().Px()`    |
| `rec_py_neg`         | `std::vector<double>` | y-component of the momentum of the vertexed (default) negative muon of the dimuon| `SRecDimuon::get_mom_neg().Py()`    |
| `rec_pz_neg`         | `std::vector<double>` | z-component of the momentum of the vertexed (default) negative muon of the dimuon| `SRecDimuon::get_mom_pos().Pz()`    |
| `rec_x_dimuon`       | `std::vector<double>` | x-component of the position of the vertexed (default) dimuon                     | `SRecDimuon::get_pos().X()`         |
| `rec_y_dimuon`       | `std::vector<double>` | y-component of the position of the vertexed (default) dimuon                     | `SRecDimuon::get_pos().Y()`         |
| `rec_z_dimuon`       | `std::vector<double>` | z-component of the position of the vertexed (default) dimuon                     | `SRecDimuon::get_pos().Z()`         |
| `rec_px_pos_tgt`     | `std::vector<double>` | x-component of the momentum of the vertexed (target) positive muon of the dimuon | `SRecDimuon::p_pos_target().Px()`   |
| `rec_py_pos_tgt`     | `std::vector<double>` | y-component of the momentum of the vertexed (target) positive muon of the dimuon | `SRecDimuon::p_pos_target().Py()`   |
| `rec_pz_pos_tgt`     | `std::vector<double>` | z-component of the momentum of the vertexed (target) positive muon of the dimuon | `SRecDimuon::p_pos_target().Pz()`   |
| `rec_px_neg_tgt`     | `std::vector<double>` | x-component of the momentum of the vertexed (target) negative muon of the dimuon | `SRecDimuon::p_neg_target.Px()`     |
| `rec_py_neg_tgt`     | `std::vector<double>` | y-component of the momentum of the vertexed (target) negative muon of the dimuon | `SRecDimuon::p_neg_target.Py()`     |
| `rec_pz_neg_tgt`     | `std::vector<double>` | z-component of the momentum of the vertexed (target) negative muon of the dimuon | `SRecDimuon::p_neg_target.Pz()`     |
| `rec_px_pos_dump`    | `std::vector<double>` | x-component of the momentum of the vertexed (dump) positive muon of the dimuon   | `SRecDimuon::p_pos_dump.Px ()`      |
| `rec_py_pos_dump`    | `std::vector<double>` | y-component of the momentum of the vertexed (dump) positive muon of the dimuon   | `SRecDimuon::p_pos_dump.Py ()`      |
| `rec_pz_pos_dump`    | `std::vector<double>` | z-component of the momentum of the vertexed (dump) positive muon of the dimuon   | `SRecDimuon::p_pos_dump.Pz ()`      |
| `rec_px_neg_dump`    | `std::vector<double>` | x-component of the momentum of the vertexed (dump) negative muon of the dimuon   | `SRecDimuon::p_neg_dump.Px ()`      |
| `rec_py_neg_dump`    | `std::vector<double>` | y-component of the momentum of the vertexed (dump) negative muon of the dimuon   | `SRecDimuon::p_neg_dump.Py ()`      |
| `rec_pz_neg_dump`    | `std::vector<double>` | z-component of the momentum of the vertexed (dump) negative muon of the dimuon   | `SRecDimuon::p_neg_dump.Pz ()`      |

## Reconstructed Track Variables
These variables store information about reconstructed muon tracks, will be obtained from the `SRecTrack` class, at the vertex, stations 1 and 3, target, and dump regions.

| Variable Name       | Type                  | Description                                                                 | User Functions                         |
|---------------------|-----------------------|-----------------------------------------------------------------------------|----------------------------------------|
| `rec_track_id`      | `std::vector<int>`    | Track ID of the recons. muon (set as the index of the vector`rec_track_id).`|                                        |
| `rec_charge`        | `std::vector<int>`    | Charge of the reconstructed muons.                                          | `SRecTrack::get_charge()`              |
| `rec_vx`            | `std::vector<double>` | x-coordinate of the reconstructed vertex.                                   | `SRecTrack::get_pos_vtx().X()`         |
| `rec_vy`            | `std::vector<double>` | y-coordinate of the reconstructed vertex.                                   | `SRecTrack::get_pos_vtx().Y()`         |
| `rec_vz`            | `std::vector<double>` | z-coordinate of the reconstructed vertex.                                   | `SRecTrack::get_pos_vtx().Z()`         |
| `rec_px`            | `std::vector<double>` | x-component of the reconstructed momentum at the vertex.                    | `SRecTrack::get_mom_vtx().Px()`        |
| `rec_py`            | `std::vector<double>` | y-component of the reconstructed momentum at the vertex.                    | `SRecTrack::get_mom_vtx().Py()`        |
| `rec_pz`            | `std::vector<double>` | z-component of the reconstructed momentum at the vertex.                    | `SRecTrack::get_mom_vtx().Pz()`        |
| `rec_x_st1`         | `std::vector<double>` | x-coordinate of the reconstructed track at station 1.                       | `SRecTrack::get_pos_st1().X()`         |
| `rec_y_st1`         | `std::vector<double>` | y-coordinate of the reconstructed track at station 1.                       | `SRecTrack::get_pos_st1().Y()`         |
| `rec_z_st1`         | `std::vector<double>` | z-coordinate of the reconstructed track at station 1.                       | `SRecTrack::get_pos_st1().Z()`         |
| `rec_px_st1`        | `std::vector<double>` | x-component of the reconstructed momentum at station 1.                     | `SRecTrack::get_mom_st1().Px()`        |
| `rec_py_st1`        | `std::vector<double>` | y-component of the reconstructed momentum at station 1.                     | `SRecTrack::get_mom_st1().Py()`        |
| `rec_pz_st1`        | `std::vector<double>` | z-component of the reconstructed momentum at station 1.                     | `SRecTrack::get_mom_st1().Pz()`        |
| `rec_x_st3`         | `std::vector<double>` | x-coordinate of the reconstructed track at station 3.                       | `SRecTrack::get_pos_st3().X()`         |
| `rec_y_st3`         | `std::vector<double>` | y-coordinate of the reconstructed track at station 3.                       | `SRecTrack::get_pos_st3().Y()`         |
| `rec_z_st3`         | `std::vector<double>` | z-coordinate of the reconstructed track at station 3.                       | `SRecTrack::get_pos_st3().Z()`         |
| `rec_px_st3`        | `std::vector<double>` | x-component of the reconstructed momentum at station 3.                     | `SRecTrack::get_mom_st3().Px()`        |
| `rec_py_st3`        | `std::vector<double>` | y-component of the reconstructed momentum at station 3.                     | `SRecTrack::get_mom_st3().Py()`        |
| `rec_pz_st3`        | `std::vector<double>` | z-component of the reconstructed momentum at station 3.                     | `SRecTrack::get_mom_st3().Pz()`        |
| `rec_num_hits`      | `std::vector<int>`    | Total hits associated with the reconstructed track.                         | `SRecTrack::get_num_hits()`            |
| `rec_chisq`         | `std::vector<double>` | Global track fit chi-squared value.                                         | `SRecTrack::get_chisq()`               |
| `rec_chisq_target`  | `std::vector<double>` | Chi-squared value of the track fit at the target.                           | `SRecTrack::get_chisq_target()`        |
| `rec_chisq_dump`    | `std::vector<double>` | Chi-squared value of the track fit at the dump.                             | `SRecTrack::get_chisq_dump()`          |
| `rec_chisq_upstream`| `std::vector<double>` | Chi-squared value of the track fit in the upstream region.                  | `SRecTrack::get_chisq_upstream()`      |
| `rec_x_tgt`         | `std::vector<double>` | x-coordinate of the reconstructed track at the target.                      | `SRecTrack::get_pos_target().X()`      |
| `rec_y_tgt`         | `std::vector<double>` | y-coordinate of the reconstructed track at the target.                      | `SRecTrack::get_pos_target().Y()`      |
| `rec_z_tgt`         | `std::vector<double>` | z-coordinate of the reconstructed track at the target.                      | `SRecTrack::get_pos_target().Z()`      |
| `rec_x_dump`        | `std::vector<double>` | x-coordinate of the reconstructed track at the dump.                        | `SRecTrack::get_pos_dump().X()`        |
| `rec_y_dump`        | `std::vector<double>` | y-coordinate of the reconstructed track at the dump.                        | `SRecTrack::get_pos_dump().Y()`        |
| `rec_z_dump`        | `std::vector<double>` | z-coordinate of the reconstructed track at the dump.                        | `SRecTrack::get_pos_dump().Z()`        |
| `rec_px_tgt`        | `std::vector<double>` | x-component of the reconstructed momentum at the target.                    | `SRecTrack::get_mom_target().Px()`     |
| `rec_py_tgt`        | `std::vector<double>` | y-component of the reconstructed momentum at the target.                    | `SRecTrack::get_mom_target().Py()`     |
| `rec_pz_tgt`        | `std::vector<double>` | z-component of the reconstructed momentum at the target.                    | `SRecTrack::get_mom_target().Pz()`     |
| `rec_px_dump`       | `std::vector<double>` | x-component of the reconstructed momentum at the dump.                      | `SRecTrack::get_mom_dump().Px()`       |
| `rec_py_dump`       | `std::vector<double>` | y-component of the reconstructed momentum at the dump.                      | `SRecTrack::get_mom_dump().Py()`       |
| `rec_pz_dump`       | `std::vector<double>` | z-component of the reconstructed momentum at the dump.                      | `SRecTrack::get_mom_dump().Pz()`       |

``` Compilation before running the Fun4All macro locally or in the grid                                                      
source setup.sh                                                                                       
cmake-this                                                                                            
make-this                                                                                             
```                                                                                                   
### Uses                                                                                              
#Converting DST to RUS
                                                                                                      
1. **Single DST File**                                                                                
   To convert a single DST file to RUS format, you can use the `Fun4Test.C` macro.                    
   Note: This macro is not configured to perform reconstruction or vertexing. Instead, it uses a vertexed DST file for processing into RUS format.  
                                                                                                      
   ```bash                                                                                            
   cd Convert                                                                                         
   root -b Fun4Test.C                                                                                 
                                                                                                      
2. **Processing Multiple DST Files**                                                                  
   If you have many DST files and want to process them locally or on the grid, use the following command:  

   ```bash
   ./gridsub.sh -j 1-5 -g -o

	1. `-j 1-5`: Specifies the range of input DST files to process (from the 1st row to the 5th one).
 	2. `-g`: Enables grid mode for processing.
	3. `-o`: Overwrites existing files.
