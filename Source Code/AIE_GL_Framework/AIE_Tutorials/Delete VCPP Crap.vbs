Dim WshShell
Set WshShell = WScript.CreateObject("WScript.Shell")
''WScript.Echo WshShell.CurrentDirectory

Dim ClearFileCounter
ClearFileCounter = 0
Dim ClearFolderCounter
ClearFolderCounter = 0

Dim TotalBytesDeleted
TotalBytesDeleted = 0


Set FSO = CreateObject("Scripting.FileSystemObject")
ShowSubfolders FSO.GetFolder(WshShell.CurrentDirectory)

WScript.Echo "Cleared up : " & ClearFileCounter & " files. " & ClearFolderCounter & " folders. For a Total of: " & TotalBytesDeleted / 1024 / 1024 & " mb."

Sub ShowSubFolders(Folder)
	For Each File in Folder.Files
		If InStr(File.Path, ".sdf") or InStr(File.Path, ".suo") Then
			''WScript.Echo File.Path
			TotalBytesDeleted = TotalBytesDeleted + File.Size
			FSO.DeleteFile File.Path

			ClearCounter = ClearCounter + 1
		End If
	Next
    For Each Subfolder in Folder.SubFolders

		If InStr(SubFolder.Path, "Debug") <> 0 or InStr(SubFolder.Path, "Release") or InStr(SubFolder.Path, "ipch") Then
			ClearFileCounter = ClearFileCounter + 1
			TotalBytesDeleted = TotalBytesDeleted + SubFolder.Size
			FSO.DeleteFolder SubFolder.Path 
		ElseIf InStr(SubFolder.Path, ".svn") = 0 Then
			ShowSubFolders Subfolder
		End If
    Next
End Sub