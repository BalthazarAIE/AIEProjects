using UnityEngine;
using System.Collections;

public class CameraSelection : MonoBehaviour {
	
	public Camera cam;
	
	public Transform HitObject; 
	
	
	RaycastHit hit;
	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
		Ray ray = cam.ScreenPointToRay(Input.mousePosition);
		
		
		
		if(Physics.Raycast(ray, out hit,1000f))
		{
			Debug.DrawLine(transform.position,hit.point,Color.green,.1f);
			HitObject = hit.collider.transform;
		}
	
		
	
	}
}
