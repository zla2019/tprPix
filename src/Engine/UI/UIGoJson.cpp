/*
 * ====================== UIGoJson.cpp =====================
 *                          -- tpr --
 *                                        CREATE -- 2019.07.02
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 */
#include "UIGoSpecFromJson.h"

//--------------- CPP ------------------//
#include <unordered_map>
#include <string>
#include <utility>

//--------------- Libs ------------------//
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "tprGeneral.h"

//-------------------- Engine --------------------//
#include "tprAssert.h"
#include "global.h"
#include "fileIO.h"

#include "json_oth.h"

#include "esrc_state.h"


using namespace rapidjson;

#include <iostream>
using std::cout;
using std::endl;

namespace json{//------------- namespace json ----------------
namespace uiJson_inn {//-------- namespace: uiJson_inn --------------//

    void parse_single_uiGoJsonFile( const std::string &path_file_ );

}//------------- namespace: uiJson_inn end --------------//




/* Do Not Worry About Performance !!!
 */
void parse_uiGoJsonFile(){

    cout << "   ----- parse_uiGoJsonFile: start ----- " << endl;


    std::vector<std::string> path_files {};
    collect_fileNames( path_jsons, "uiGos", "_files.json", path_files );
    //---
    for( const auto &i : path_files ){
        uiJson_inn::parse_single_uiGoJsonFile(i);
    }

    esrc::insertState("json_uiGo");
    cout << "   ----- parse_uiGoJsonFile: end ----- " << endl;
}



namespace uiJson_inn {//-------- namespace: uiJson_inn --------------//



void parse_single_uiGoJsonFile( const std::string &path_file_ ){
    //-----------------------------//
    //         load file
    //-----------------------------//
    auto jsonBufUPtr = read_a_file( path_file_ );

    //-----------------------------//
    //      parce JSON data
    //-----------------------------//
    Document doc;
    doc.Parse( jsonBufUPtr->c_str() );

    goSpeciesId_t        speciesId {};

    tprAssert( doc.IsArray() );
    for( auto &ent : doc.GetArray() ){


        {//--- speciesId ---//
            const auto &a = check_and_get_value( ent, "speciesId", JsonValType::Uint );
            speciesId = static_cast<goSpeciesId_t>( a.GetUint() );
        }

        UIGoSpecFromJson &uiGoJsonDataRef = UIGoSpecFromJson::create_new_UIGoSpecFromJson( speciesId );
        uiGoJsonDataRef.speciesId = speciesId;

        {//--- goSpeciesName ---//
            const auto &a = check_and_get_value( ent, "goSpeciesName", JsonValType::String );
            uiGoJsonDataRef.goSpeciesName = a.GetString();
        }
        {//--- family ---//
            const auto &a = check_and_get_value( ent, "family", JsonValType::String );
            uiGoJsonDataRef.family = str_2_GameObjFamily( a.GetString() );
        }
        {//--- moveType ---//
            const auto &a = check_and_get_value( ent, "moveType", JsonValType::String );
            uiGoJsonDataRef.moveType = str_2_MoveType( a.GetString() );
        }
        {//--- speedLvl ---//
            const auto &a = check_and_get_value( ent, "speedLvl", JsonValType::Int );
            uiGoJsonDataRef.speedLvl = int_2_SpeedLevel( a.GetInt() );
        }

        //------------------------------------//
        UIGoSpecFromJson::insert_2_uiGoSpeciesIds_names_containers(uiGoJsonDataRef.speciesId, 
                                                                uiGoJsonDataRef.goSpeciesName );

    }
}



}//------------- namespace: uiJson_inn end --------------//
}//------------- namespace json: end ----------------
