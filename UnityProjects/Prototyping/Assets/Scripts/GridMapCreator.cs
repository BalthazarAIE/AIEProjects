using UnityEngine;
using System.Collections;

public class GridMapCreator : MonoBehaviour {
	
	
	public int gridXSize=2;
	public int gridYSize=2;
	public int gridObjectSize = 10;
	
	public GameObject[] Tiles;
	
	public GameObject Tile;
	
	private Vector3 tempPosition = Vector3.zero;
	// Use this for initialization
	void Start () {
		Tiles = new GameObject[gridXSize*gridYSize];
		CreateGrid();
		
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	void CreateGrid()
	{
		int j =0;
		for(int i = 0; i < gridXSize; i++)
		{
			

			for(j = 0; j < gridYSize; j++)
			{
				Tiles[i *(j +1)]= Instantiate(Tile,tempPosition,Quaternion.identity) as GameObject;
				Tiles[i *(j +1)].name = "Tile( " + i +" , " + j + " )";
				tempPosition.z += gridObjectSize;
			}
			tempPosition.z = 0;
			tempPosition.x += gridObjectSize;
			
		} 
		
	}
	
}
