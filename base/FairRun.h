#ifndef FAIRRUN_H
#define FAIRRUN_H

#include "TNamed.h"
#include "FairLogger.h"
class FairTask;
class TFile;
class FairFileHeader;
class FairRuntimeDb;
class FairRootManager;
class FairEventHeader;

/**
 * Configure the Simuation or Analysis
 * @author M. Al-Turany  D. Bertini
 * @version 0.1
 * @since 12.01.04
 */

class FairRun : public TNamed
{
  public:
    /**
     * default ctor
     */
    FairRun();
    /**
    * default dtor
    */
    virtual ~FairRun();
    /**
     * static instance
     */
    static FairRun* Instance();
    /**
     * Add a FAIRTask to the simulation or analysis
     */
    virtual void       AddTask(FairTask* t);
    virtual void       SetTask(FairTask* t);
    /**
     * Initialize the Simulation or analysis
     */
    virtual void    Init()=0;
    /**
     * run the analysis or simulation
    */
    virtual void    Run(Int_t NStart =0,Int_t NStop=0)=0;
    /**
     * Set the output file name for analysis or simulation
    */
    void        SetOutputFile(const char* fname);
    /**
     * Set the output file for analysis or simulation
    */
    void        SetOutputFile(TFile* f);
    /**
     *       Set the experiment dependent run header
     *       for each run
     */
    void        SetEventHeader(FairEventHeader* EvHeader)  {
      fEvHead=EvHeader;
    }
    /**
     * return a pointer to the RuntimeDB
     */
    FairRuntimeDb* GetRuntimeDb(void) {
      return fRtdb;
    }
    /**
     * return a pointer to the output file
     */
    TFile* GetOutputFile() {
      return fOutFile;
    }
    /**
     * return the run ID for the actul run
     */
    Int_t  GetRunId() {
      return ((Int_t) fRunId);
    }

    /**Get the detector specific run header*/
    FairEventHeader*  GetEventHeader();
    /**
    * return true for Anaylsis session
    */
    Bool_t            IsAna() {
      return fAna;
    }
    /**
    *Get task by name
    */

    FairTask* GetTask(const char* taskName);
    /**
    *Get Main Task
    */
    FairTask* GetMainTask() {
      return fTask;
    }
    /**
    * Return the number of Tasks added to this Run
    */
    Int_t     GetNTasks() {
      return fNTasks;
    }

    /**Create a new file and save the TGeoManager to it*/

    void CreateGeometryFile(const char* geofile);

  private:
    FairRun(const FairRun& M);
    FairRun& operator= (const  FairRun&) {
      return *this;
    }
    /** Number of Tasks added*/
    Int_t fNTasks;

  protected:
    /** Fair Logger */
    FairLogger*             fLogger;//!
    /** static pointer to this run*/
    static FairRun*          fRunInstance;
    /** RuntimeDb*/
    FairRuntimeDb*           fRtdb;
    /** Tasks used*/
    FairTask*                fTask;
    /**Output file name*/
    const char*              fOutname;
    /**IO manager */
    FairRootManager*         fRootManager;
    /**Output file*/
    TFile*                   fOutFile;
    /**Run Id*/
    UInt_t                   fRunId;//!
    /** true for Anaylsis session*/
    Bool_t                   fAna;  //!
    /** MC Event Header */
    FairEventHeader*         fEvHead; //!
    /** File  Header */
    FairFileHeader*          fFileHeader;

    ClassDef(FairRun ,1)
};
#endif //FAIRRUN_H
