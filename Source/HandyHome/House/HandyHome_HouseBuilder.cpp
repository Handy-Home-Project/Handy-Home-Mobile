// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyHome_HouseBuilder.h"
#include "HandyHome_HouseData.h"
#include "HandyHome_House.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

UHandyHome_HouseBuilder::UHandyHome_HouseBuilder()
{
	//BuildHouse();
	
}

void UHandyHome_HouseBuilder::BuildHouse()
{
	ReadData();
}

void UHandyHome_HouseBuilder::ReadData()
{
	FString JsonString;

	checkf(
		FFileHelper::LoadFileToString(
			JsonString,
			*(FPaths::ProjectContentDir() + FString(TEXT("/HouseData/HouseData.json")))
		),
		TEXT("House Data Loading Has Failed!")
	);

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

	TSharedPtr<FJsonObject> JsonObj = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObj) && JsonObj.IsValid())
	{
		TSharedPtr<FJsonObject>* HomeJsonObj;
		checkf(JsonObj->Values[TEXT("home")]->TryGetObject(HomeJsonObj), TEXT("Wrong Field Name!"));

		TArray<TSharedPtr<FJsonValue>>* RoomListJsonArray;
		checkf((*HomeJsonObj)->Values[TEXT("room_list")]->TryGetArray(RoomListJsonArray), TEXT("Wrong Field Name!"));


		const int32 RoomListJsonObjSize = (*RoomListJsonArray).Num();
		for (int32 i = 0; i < RoomListJsonObjSize; i++)
		{
			TSharedPtr<FJsonObject>* RoomNameJsonObj;
			checkf((*RoomListJsonArray)[i]->TryGetObject(RoomNameJsonObj), TEXT("Empty Object!"));

			FString RoomName;	//방 이름.
			checkf((*RoomNameJsonObj)->Values[TEXT("room_name")]->TryGetString(RoomName), TEXT("Wrong Field Name!"));

			TArray<TSharedPtr<FJsonValue>>* VertexArray;
			checkf((*RoomNameJsonObj)->Values[TEXT("vertexes")]->TryGetArray(VertexArray), TEXT("Wrong Field Name!"));

			TArray<TSharedPtr<FJsonValue>> IthVertexPair;
			IthVertexPair.Reserve(2);

			const int32 VertexArraySize = VertexArray->Num();
			for (int32 j = 0; j < VertexArraySize; j++)
			{
				IthVertexPair = (*VertexArray)[j]->AsArray();
				
				const FVector2D VertexCoord = FVector2D(
					IthVertexPair[0]->AsNumber(),
					IthVertexPair[1]->AsNumber()
				);

				IthVertexPair.Reset();
				
				//디버깅용 꼭지점 그리는 함수.
				DrawDebugSphere(GetWorld(), FVector(VertexCoord.X, VertexCoord.Y, 0.0), 14.f, 16, FColor::Red, false, 4444.f);
			}
		}
	}
}
