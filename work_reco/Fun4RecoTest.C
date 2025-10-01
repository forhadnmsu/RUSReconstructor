#include <top/G4_Beamline.C>
#include <top/G4_Target.C>
#include <top/G4_InsensitiveVolumes.C>
#include <top/G4_SensitiveDetectors.C>

R__LOAD_LIBRARY(libdimu_ana_rus)
R__LOAD_LIBRARY(libfun4all)
R__LOAD_LIBRARY(libg4detectors)
R__LOAD_LIBRARY(libg4testbench)
R__LOAD_LIBRARY(libg4eval)
R__LOAD_LIBRARY(libg4dst)
R__LOAD_LIBRARY(libdptrigger)
R__LOAD_LIBRARY(libembedding)
R__LOAD_LIBRARY(libevt_filter)
R__LOAD_LIBRARY(libktracker)
R__LOAD_LIBRARY(libcalibrator)

int Fun4RecoTest(const int nevent = 10){

    const double target_coil_pos_z = -300;
    const double target_l = 7.9; //cm
    const double target_z = (7.9-target_l)/2.; //cm
    const int use_g4steps = 1;
    int embedding_opt = 0;

    const double FMAGSTR = -1.044;
    const double KMAGSTR = -1.025;

    const bool do_collimator = true;
    const bool do_target = true;
    const bool do_e1039_shielding = true;
    const bool do_fmag = true;
    const bool do_kmag = true;
    const bool do_absorber = true;
    const bool do_dphodo = true;
    const bool read_hepmc   = false;
    const bool do_station1DC = false;       //station-1 drift chamber should be turned off by default


    recoConsts *rc = recoConsts::instance();
    rc->set_IntFlag("RUNNUMBER", 5433); /// The geometry is selected based on run number.
    rc->set_DoubleFlag("FMAGSTR", FMAGSTR);
    rc->set_DoubleFlag("KMAGSTR", KMAGSTR);
    rc->set_DoubleFlag("SIGX_BEAM", 0.3);
    rc->set_DoubleFlag("SIGY_BEAM", 0.3);
    rc->set_DoubleFlag("Z_UPSTREAM", -700.);

    Fun4AllServer* se = Fun4AllServer::instance();
    se->setRun(5433);


    CalibDriftDist* cal_dd = new CalibDriftDist();
    se->registerSubsystem(cal_dd);

    // Fun4All G4 module
    PHG4Reco *g4Reco = new PHG4Reco();
    //PHG4Reco::G4Seed(123);
    g4Reco->set_field_map();
    // size of the world - every detector has to fit in here
    g4Reco->SetWorldSizeX(1000);
    g4Reco->SetWorldSizeY(1000);
    g4Reco->SetWorldSizeZ(5000);
    // shape of our world - it is a tube
    g4Reco->SetWorldShape("G4BOX");
    // this is what our world is filled with
    g4Reco->SetWorldMaterial("G4_AIR"); //G4_Galactic, G4_AIR
    // Geant4 Physics list to use
    g4Reco->SetPhysicsList("FTFP_BERT");

    // insensitive elements of the spectrometer
    SetupInsensitiveVolumes(g4Reco, do_e1039_shielding, do_fmag, do_kmag, do_absorber);

    // collimator, targer and shielding between target and FMag
    SetupBeamline(g4Reco, do_collimator, target_coil_pos_z - 302.36); // Is the position correct??


    if (do_target) {
        SetupTarget(g4Reco, target_coil_pos_z, target_l, target_z, use_g4steps);
    }

    // sensitive elements of the spectrometer
    SetupSensitiveDetectors(g4Reco, do_dphodo, do_station1DC);

    se->registerSubsystem(g4Reco);


    // digitizer
    SQDigitizer *digitizer = new SQDigitizer("DPDigitizer", 0);
    //digitizer->Verbosity(99);
    digitizer->set_enable_st1dc(do_station1DC);    // these two lines need to be in sync with the parameters used
    digitizer->set_enable_dphodo(do_dphodo);       // in the SetupSensitiveVolumes() function call above
    se->registerSubsystem(digitizer);


    SQReco* reco = new SQReco();
    reco->Verbosity(1);
    reco->set_legacy_rec_container(false); 
    reco->set_geom_file_name((string)gSystem->Getenv("E1039_RESOURCE") + "/geometry/geom_run005433.root");
    reco->set_enable_KF(true);
    reco->setInputTy(SQReco::E1039);
    reco->setFitterTy(SQReco::KFREF);
    reco->set_evt_reducer_opt("none");
    reco->set_enable_eval_dst(true);
    for (int ii = 0; ii <= 3; ii++) reco->add_eval_list(ii);
    reco->set_enable_eval(true);
    se->registerSubsystem(reco);

    SQVertexing* vtx = new SQVertexing();
    vtx->Verbosity(100);
    se->registerSubsystem(vtx);

    Fun4AllInputManager *in_ = new Fun4AllDummyInputManager("DUMMY");
    se->registerInputManager(in_);

    Fun4AllRUSInputManager* in = new Fun4AllRUSInputManager("VectIn");
    //in->Verbosity(99);
    in->set_tree_name("tree");
    in->fileopen("RUS_DY.root");
    se->registerInputManager(in);



    //Fun4AllRUSOutputManager* tree = new Fun4AllRUSOutputManager();
    //tree->SetTreeName("tree");
    //tree->SetFileName("RUS.root");
    //se->registerOutputManager(tree);


    // DST output manager
    Fun4AllDstOutputManager *out = new Fun4AllDstOutputManager("DSTOUT", "DST.root");
    se->registerOutputManager(out);

    se->run(20);
    se->End();
    delete se;
    exit(0); //return 0;
}
