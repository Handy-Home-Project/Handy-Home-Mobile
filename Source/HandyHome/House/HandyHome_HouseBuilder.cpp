// Fill out your copyright notice in the Description page of Project Settings.


#include "HandyHome_HouseBuilder.h"
#include "HandyHome_House.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"

UHandyHome_HouseBuilder::UHandyHome_HouseBuilder()
{
	
}

void UHandyHome_HouseBuilder::BuildHouse()
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

		TSharedPtr<FJsonObject>* RoomNameJsonObj;	//"room_name" 필드에 있는 모든 데이터를 저장한 JsonObject.
		FString RoomName;	//방 이름.
		TArray<TSharedPtr<FJsonValue>>* VertexArray;	//방 벽들의 정점 좌표들.
		TArray<TSharedPtr<FJsonValue>> VertexPair;	//정점의 XY 좌표값.
		VertexPair.Reserve(2);

		for (TActorIterator<AHandyHome_House> It(GetWorld()); It; ++It)
		{
			It.ClearCurrent();
			//기존 하우스가 몇 개 있든 다 삭제한다.
			//문제 생길 가능성 높음.
		}

		TObjectPtr<AHandyHome_House> House = GetWorld()->SpawnActor<AHandyHome_House>();

		const int32 RoomListJsonObjSize = (*RoomListJsonArray).Num();
		House->HouseData.RoomDataMap.Reserve(RoomListJsonObjSize);
		for (int32 i = 0; i < RoomListJsonObjSize; i++)
		{
			checkf((*RoomListJsonArray)[i]->TryGetObject(RoomNameJsonObj), TEXT("Empty Object!"));

			checkf((*RoomNameJsonObj)->Values[TEXT("room_name")]->TryGetString(RoomName), TEXT("Wrong Field Name!"));

			checkf((*RoomNameJsonObj)->Values[TEXT("vertexes")]->TryGetArray(VertexArray), TEXT("Wrong Field Name!"));

			VertexPair = (*VertexArray)[0]->AsArray();
			FVector2D PrevVertexCoord = FVector2D(	//이전 벽의 끝점 == 새 벽의 시작점. 
				VertexPair[0]->AsNumber(),
				VertexPair[1]->AsNumber()
			);

			//디버깅용 방 꼭지점 그리는 함수. 나중에 벽 생성 기능 완성되면 지울 것.
			DrawDebugSphere(GetWorld(), FVector(PrevVertexCoord.X, PrevVertexCoord.Y, 0.0), 14.f, 16, FColor::Red, false, 4444.f);

			VertexPair.Reset();

			FRoomData* RoomData = &House->HouseData.RoomDataMap.Emplace(RoomName);
			const int32 VertexArraySize = VertexArray->Num();
			RoomData->WallDataArray.Reserve(VertexArraySize);
			for (int32 j = 1; j < VertexArraySize; j++)
			{
				VertexPair = (*VertexArray)[j]->AsArray();

				const FVector2D CurVertexCoord = FVector2D(
					VertexPair[0]->AsNumber(),
					VertexPair[1]->AsNumber()
				);

				VertexPair.Reset();

				//디버깅용 방 꼭지점 그리는 함수. 나중에 벽 생성 기능 완성되면 지울 것.
				DrawDebugSphere(GetWorld(), FVector(CurVertexCoord.X, CurVertexCoord.Y, 0.0), 14.f, 16, FColor::Red, false, 4444.f);

				RoomData->WallDataArray.Emplace(
					FName(RoomName + FString::Printf(TEXT("_%d"), j - 1)),
					FVector2D(abs(CurVertexCoord.X - PrevVertexCoord.X), abs(CurVertexCoord.Y - PrevVertexCoord.Y)),
					FVector2D((PrevVertexCoord.X + CurVertexCoord.X) * 0.5, (PrevVertexCoord.Y + CurVertexCoord.Y) * 0.5)
				);
				House->HouseData.WallCount++;

				PrevVertexCoord = CurVertexCoord;
			}

			VertexArray->Reset();
			RoomName.Reset();
		}

		House->Build();
	}
}